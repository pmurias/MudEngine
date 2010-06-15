#include <MudCharacterEntity.h>
#include <MudCharacterEntityTemplate.h>
#include <MudCharacterEntityProperties.h>
#include <MudAction.h>
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
        state = 0;
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
        Core::GetInstance().bulWorld->addRigidBody(body);

        Core::GetInstance().bulBroadphase->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());

        ghostShape = new btCylinderShape(btVector3(radius, height, radius));

        ghostObject = new btPairCachingGhostObject();
        ghostObject->setWorldTransform(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));
        ghostObject->setCollisionShape(ghostShape);
        ghostObject->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
        ghostObject->setUserPointer(this);

        Core::GetInstance().bulWorld->addCollisionObject(ghostObject,
                btBroadphaseProxy::SensorTrigger | btBroadphaseProxy::StaticFilter,
                btBroadphaseProxy::AllFilter);
    }

    CharacterEntity::~CharacterEntity() {
    }

    void CharacterEntity::Update() {
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
                VisibleEntity *entity = static_cast<VisibleEntity *>(ghostObject->getOverlappingObject(i)->getUserPointer());
                if (entity && (entity != this)) {
                    focusedEntity = entity;
                    break;
                }
            }
        }
    }

    void CharacterEntity::UpdateBehaviour() {


        if (state & CS_IDLE) {
            desiredMoveVelocity = btVector3(0,0,0);
        }
        if (state & CS_MOVING_FORWARD) {                
            Ogre::Vector3 forward = node->getOrientation() * Ogre::Vector3::UNIT_Z;
            forward *= walkSpeed * (state & CS_RUNNING ? runFactor : 1.0);
            desiredMoveVelocity = Utils::OgreVec3ToBt(forward);
        }

        if (state & CS_TURNING_LEFT) {
            Ogre::Quaternion turn = Ogre::Vector3(0,0,1).getRotationTo(Ogre::Vector3(0.1, 0, 1));
            node->setOrientation(node->getOrientation() * turn);
        }
        if (state & CS_TURNING_RIGHT) {
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
        state &= ~CS_IDLE;
        state |= CS_MOVING_FORWARD;
    }

    void CharacterEntity::StopMoving() {
        state &= ~CS_MOVING_FORWARD;
        state |= CS_IDLE;
    }

    void CharacterEntity::TurnLeft() {
        state |= CS_TURNING_LEFT;
    }

    void CharacterEntity::TurnRight() {
        state |= CS_TURNING_RIGHT;
    }

    void CharacterEntity::StopTurning() {
        state &= ~(CS_TURNING_LEFT | CS_TURNING_RIGHT);
    }

    void CharacterEntity::Run() {
        state |= CS_RUNNING;
        state &= ~CS_WALKING;
    }

    void CharacterEntity::Walk() {
        state |= CS_WALKING;
        state &= ~CS_RUNNING;
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
    		focusedEntity->ActionPerform(new Action(focusedEntity->GetDefaultActionType(), this));
    	}
    }
}

