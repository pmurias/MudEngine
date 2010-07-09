#include <events/MudCharacterPickedCollectableEvent.h>
#include <events/MudCharacterOpenedContainerEvent.h>
#include <events/MudCharacterClosedContainerEvent.h>
#include <MudCharacterEntity.h>
#include <MudCharacterEntityTemplate.h>
#include <MudCharacterEntityProperties.h>
#include <MudCharacterAnimationBlender.h>
#include <MudInventory.h>
#include <MudItem.h>
#include <MudUtils.h>
#include <MudCore.h>

#include <BulletCollision/CollisionDispatch/btGhostObject.h>

namespace Mud {

    CharacterEntity::CharacterEntity(const char *name, const char *entityTemplateName) 
        : VisibleEntity(name, entityTemplateName) {
        CharacterEntityTemplate *entTemplate = 
            static_cast<CharacterEntityTemplate*>(Core::GetInstance().entityTemplateManager.GetTemplate(entityTemplateName));     

        *(static_cast<CharacterEntityProperties *>(this)) = *(static_cast<CharacterEntityProperties*>(entTemplate));
        generalState = CS_IDLE;
        turningState = CT_NONE;
        focusedEntity = NULL;
        inventory = new Inventory();

        entity = Core::GetInstance().ogreSceneMgr->createEntity(name, entTemplate->meshName);
        node = Core::GetInstance().ogreSceneMgr->getRootSceneNode()->createChildSceneNode(name);
        node->attachObject(entity);

        collisionShape = new btCapsuleShape(radius, height);

        btDefaultMotionState *motionState = new btDefaultMotionState(
            btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0))
            );

        btVector3 inertia(0,0,0);
        collisionShape->calculateLocalInertia(mass, inertia);
        btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(
                mass,
                motionState,
                collisionShape,
                inertia
            );

        body = new btRigidBody(rigidBodyCI);
        body->setUserPointer(static_cast<void *>(this));
        body->setActivationState(DISABLE_DEACTIVATION);
        body->setFriction(0.0);
        body->setAngularFactor(btVector3(0, 1, 0));
        body->setDamping(0.9, 0.9);
        Core::GetInstance().bulWorld->addRigidBody(body);

        Core::GetInstance().bulBroadphase->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());

        ghostShape = new btCylinderShape(btVector3(radius, height, radius));

        ghostObject = new btPairCachingGhostObject();
        ghostObject->setWorldTransform(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));
        ghostObject->setCollisionShape(ghostShape);
        ghostObject->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);

        Core::GetInstance().bulWorld->addCollisionObject(ghostObject,
                btBroadphaseProxy::SensorTrigger | btBroadphaseProxy::StaticFilter,
                btBroadphaseProxy::AllFilter);

        animationBlender = new CharacterAnimationBlender(this);
    }

    CharacterEntity::~CharacterEntity() {
    }

    void CharacterEntity::Update() {
    	animationBlender->Update();
        UpdateBehaviour();
        UpdatePosition();
        UpdateFocus();
    }

    void CharacterEntity::SetPosition(Ogre::Vector3 pos) {
        body->setWorldTransform(btTransform(btQuaternion(0,0,0,1), Utils::OgreVec3ToBt(pos)));
    }

    void CharacterEntity::UpdatePosition() {
        node->setPosition(Utils::BtVec3ToOgre(body->getWorldTransform().getOrigin()));

        Ogre::Vector3 offset = (node->getOrientation() * Ogre::Vector3::UNIT_Z) * radius * 2.0;
        ghostObject->setWorldTransform(btTransform(btQuaternion(0,0,0,1), Utils::OgreVec3ToBt(node->getPosition() + offset)));
    }

    void CharacterEntity::UpdateFocus() {
        focusedEntity = NULL;
        int numOverlappingObjects = ghostObject->getNumOverlappingObjects();
        if (numOverlappingObjects) {
            for (int i = 0; i < numOverlappingObjects; i++) {
                if (ghostObject->getOverlappingObject(i)->getUserPointer() != NULL) {
                	VisibleEntity *entity = static_cast<VisibleEntity *>(ghostObject->getOverlappingObject(i)->getUserPointer());
                	if (entity && (entity != this) && (static_cast<void*>(entity) != static_cast<void*>(&Core::GetInstance().world))) {
                		focusedEntity = entity;
                		break;
                	}
                }
            }
        }
    }

    void CharacterEntity::UpdateBehaviour() {

    	if (generalState == CS_PICKING) {
    		animationBlender->SetAnimation(CAS_PICK);
    		desiredMoveVelocity = btVector3(0,0,0);

    		if (pickingPhase == CPP_BEFORE_PICK) {
    			if (animationBlender->GetTimePosition(CAS_PICK) >= animationBlender->GetLength(CAS_PICK) * 0.5f) {
    				Core::GetInstance().eventManager.QueueEvent(new CharacterPickedCollectableEvent(this, pickingParam));
    				pickingPhase = CPP_AFTER_PICK;
    			}
    		} else {
    			if (animationBlender->GetTimePosition(CAS_PICK) >= animationBlender->GetLength(CAS_PICK) * 0.9f) {
    				generalState = CS_IDLE;
    			}
    		}
    	} else
    	if (generalState == CS_OPENING) {
    		animationBlender->SetAnimation(CAS_OPEN_MIDDLE);
			desiredMoveVelocity = btVector3(0,0,0);

			if (animationBlender->GetTimePosition(CAS_OPEN_MIDDLE) >= animationBlender->GetLength(CAS_OPEN_MIDDLE) * 0.9f) {
				Core::GetInstance().eventManager.QueueEvent(new CharacterOpenedContainerEvent(this, openCloseParam));
				generalState = CS_IDLE;
			}
    	} else
    	if (generalState == CS_CLOSING) {
			animationBlender->SetAnimation(CAS_CLOSE_MIDDLE);
			desiredMoveVelocity = btVector3(0,0,0);

			if (animationBlender->GetTimePosition(CAS_CLOSE_MIDDLE) >= animationBlender->GetLength(CAS_CLOSE_MIDDLE) * 0.9f) {
				Core::GetInstance().eventManager.QueueEvent(new CharacterClosedContainerEvent(this, openCloseParam));
				generalState = CS_IDLE;
			}
		}


        if (generalState == CS_IDLE) {
        	animationBlender->SetAnimation(CAS_IDLE);
            desiredMoveVelocity = btVector3(0,0,0);
			body->setFriction(0.85);
        } else
        if (generalState == CS_MOVING_FORWARD) {
        	body->setFriction(0.0);
            Ogre::Vector3 forward = node->getOrientation() * Ogre::Vector3::UNIT_Z;
            forward *= walkSpeed * ((walkingState == CM_RUN) ? runFactor : 1.0);
            desiredMoveVelocity = Utils::OgreVec3ToBt(forward);

            if (walkingState == CM_RUN) {
            	animationBlender->SetAnimation(CAS_RUN_NOTHING);
            	animationBlender->SetSpeed(CAS_RUN_NOTHING, 0.7f);
            }
            else {
            	animationBlender->SetAnimation(CAS_WALK_NOTHING);
            	animationBlender->SetSpeed(CAS_WALK_NOTHING, 0.55f);
            }
        }

        if (turningState == CT_LEFT) {
            Ogre::Quaternion turn = Ogre::Vector3(0,0,1).getRotationTo(Ogre::Vector3(0.1, 0, 1));
            node->setOrientation(node->getOrientation() * turn);
        } else
        if (turningState == CT_RIGHT) {
            Ogre::Quaternion turn = Ogre::Vector3(0,0,1).getRotationTo(Ogre::Vector3(-0.1, 0, 1));
            node->setOrientation(node->getOrientation() * turn);
        }

        body->setLinearVelocity(btVector3(
            desiredMoveVelocity.x(),
            body->getLinearVelocity().y(),
            desiredMoveVelocity.z()
        ));
    }

    void CharacterEntity::StartMovingForward() {
    	if (generalState != CS_PICKING && generalState != CS_OPENING && generalState != CS_CLOSING) {
    		generalState = CS_MOVING_FORWARD;
    	}
    }

    void CharacterEntity::StopMoving() {
    	if (generalState != CS_PICKING && generalState != CS_OPENING && generalState != CS_CLOSING) {
    		generalState = CS_IDLE;
    	}
    }

    void CharacterEntity::StartTurningLeft() {
    	if (generalState != CS_PICKING && generalState != CS_OPENING && generalState != CS_CLOSING) {
    		turningState = CT_LEFT;
    	}
    }

    void CharacterEntity::StartTurningRight() {
    	if (generalState != CS_PICKING && generalState != CS_OPENING && generalState != CS_CLOSING) {
    		turningState = CT_RIGHT;
    	}
    }

    void CharacterEntity::StopTurning() {
    	turningState = CT_NONE;
    }

    void CharacterEntity::StartRunning() {
    	walkingState = CM_RUN;
    }

    void CharacterEntity::StartWalking() {
    	walkingState = CM_WALK;
    }

    void CharacterEntity::StartPicking(CollectableEntity *target) {
    	if (generalState != CS_PICKING && generalState != CS_OPENING && generalState != CS_CLOSING) {
    		generalState = CS_PICKING;
    		turningState = CT_NONE;
    		pickingParam = target;
    		pickingPhase= CPP_BEFORE_PICK;

    		animationBlender->SetTimePosition(CAS_PICK, 0.0f);
    		LookAt(target);
    	}
    }

    void CharacterEntity::StartOpening(OpenableContainerEntity *target) {
    	if (generalState != CS_PICKING && generalState != CS_OPENING && generalState != CS_CLOSING) {
    		generalState = CS_OPENING;
    		openCloseParam = target;
    		animationBlender->SetTimePosition(CAS_OPEN_MIDDLE, 0.0f);
			target->ToggleState();
    		LookAt(target);
    	}
    }

    void CharacterEntity::StartClosing(OpenableContainerEntity *target) {
		if (generalState != CS_PICKING && generalState != CS_OPENING && generalState != CS_CLOSING) {
			generalState = CS_CLOSING;
			openCloseParam = target;
			animationBlender->SetTimePosition(CAS_CLOSE_MIDDLE, 0.0f);
			target->ToggleState();
			LookAt(target);
		}
	}

	void CharacterEntity::LookAt(VisibleEntity *target) {
		node->setOrientation(Ogre::Vector3::UNIT_Z.getRotationTo((target->node->getPosition()-node->getPosition()) * Ogre::Vector3(1,0,1)));
	}

    bool CharacterEntity::IsOnGround() {
        btVector3 rayBegin = Utils::OgreVec3ToBt(node->getPosition());
        btVector3 rayEnd = Utils::OgreVec3ToBt(node->getPosition() - Ogre::Vector3(0, height * 1.05, 0));
        Utils::ClosestNotMeRayResultCallback rayCallback =
            Utils::ClosestNotMeRayResultCallback(body);
        Core::GetInstance().bulWorld->rayTest(rayBegin, rayEnd, rayCallback);

        return rayCallback.hasHit();
    }

    void CharacterEntity::Pick(Item *item) {
    	inventory->AddItem(item);
    	Core::GetInstance().console.Print("%s picked %s", name.c_str(), item->itemTemplate->name.c_str());
    }

    ActionType CharacterEntity::GetDefaultActionType() {
    	return AT_DEFAULT;
    }

    void CharacterEntity::PerfromDefaultActionOnFocusedEntity() {
    	if (focusedEntity) {
    		switch (focusedEntity->GetDefaultActionType()) {
				case(AT_PICK): {
					if (Core::GetInstance().entityManager.IsQueuedToDestroy(focusedEntity) == false) {
						StartPicking(static_cast<CollectableEntity*>(focusedEntity));
						focusedEntity = NULL;
					}
					break;
				}
				case (AT_TOGGLE_CONTAINER_STATE): {
					if (Core::GetInstance().entityManager.IsQueuedToDestroy(focusedEntity) == false) {
						if (static_cast<OpenableContainerEntity*>(focusedEntity)->CanCharacterAccessIt(this)) {
							if (static_cast<OpenableContainerEntity*>(focusedEntity)->isOpen == false) {
								StartOpening(static_cast<OpenableContainerEntity*>(focusedEntity));
							} else {
								StartClosing(static_cast<OpenableContainerEntity*>(focusedEntity));
							}
						}

						focusedEntity = NULL;
					}
					break;
				}
    		}
    	}
    }
}

