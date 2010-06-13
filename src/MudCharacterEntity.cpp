#include <MudCharacterEntity.h>
#include <MudCharacterEntityTemplate.h>
#include <MudCharacterEntityProperties.h>
#include <MudCore.h>
#include <MudUtils.h>

#include <BulletCollision/CollisionDispatch/btGhostObject.h>

namespace Mud {

    CharacterEntity::CharacterEntity(const char *name, const char *entityTemplateName) 
        : VisibleEntity(name, entityTemplateName) {
        CharacterEntityTemplate *entTemplate = 
            static_cast<CharacterEntityTemplate*>(Core::GetInstance().entityTemplateManager.GetTemplate(entityTemplateName));     

        *(static_cast<CharacterEntityProperties *>(this)) = *(static_cast<CharacterEntityProperties*>(entTemplate));
        state = 0;
        focusedEntity = NULL;

        entity = Core::GetInstance().ogreSceneMgr->createEntity(name, entTemplate->meshName);
        node = Core::GetInstance().ogreSceneMgr->getRootSceneNode()->createChildSceneNode(name);
        node->attachObject(entity);

        collisionShape = new btCapsuleShape(radius, height);

            btDefaultMotionState *motionState = new btDefaultMotionState(
                btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0))
                );

            btVector3 inertia(0,0,0);
            collisionShape->calculateLocalInertia(0, inertia);
            btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(
                    0, 
                    motionState, 
                    collisionShape, 
                    inertia
                );

            body = new btRigidBody(rigidBodyCI);
            body->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);
            body->setUserPointer(static_cast<void *>(this));
            Core::GetInstance().bulWorld->addRigidBody(body, btBroadphaseProxy::CharacterFilter,
                    btBroadphaseProxy::AllFilter);

        Core::GetInstance().bulBroadphase->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());

        ghostObject = new btPairCachingGhostObject();
        ghostObject->setWorldTransform(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));
        ghostObject->setCollisionShape(collisionShape);
        ghostObject->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
        ghostObject->setUserPointer(this);

        bodyController = new btKinematicCharacterController(ghostObject, (btConvexShape*)(collisionShape), 0.2);

        actionCollisionShape = new btCylinderShape(btVector3(radius, height, radius));

        actionObject = new btPairCachingGhostObject();
        actionObject->setWorldTransform(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));
        actionObject->setCollisionShape(actionCollisionShape);
        actionObject->setCollisionFlags(actionObject->getCollisionFlags() | btCollisionObject::CF_NO_CONTACT_RESPONSE);
        

        Core::GetInstance().bulWorld->addCollisionObject(
            ghostObject, 
            btBroadphaseProxy::DefaultFilter, 
            btBroadphaseProxy::StaticFilter |
            btBroadphaseProxy::DefaultFilter);

        Core::GetInstance().bulWorld->addCollisionObject(
            actionObject,
            btBroadphaseProxy::SensorTrigger,
            btBroadphaseProxy::AllFilter
        );

        Core::GetInstance().bulWorld->addAction(bodyController);
    }

    void CharacterEntity::Destroy() {
    }

    void CharacterEntity::Update() {
        UpdateBehaviour();
        UpdatePosition();
        UpdateFocus();
    }

    void CharacterEntity::SetPosition(Ogre::Vector3 pos) {
        bodyController->warp(Utils::OgreVec3ToBt(pos));
    }

    void CharacterEntity::UpdatePosition() {
        node->setPosition(Utils::BtVec3ToOgre(ghostObject->getWorldTransform().getOrigin()));
        Ogre::Vector3 offset = (node->getOrientation() * Ogre::Vector3::UNIT_Z) * radius * 2.0;

        actionObject->setWorldTransform(btTransform(btQuaternion(0,0,0,1), Utils::OgreVec3ToBt(node->getPosition() + offset)));    
        body->setWorldTransform(btTransform(btQuaternion(0,0,0,1), Utils::OgreVec3ToBt(node->getPosition())));
    }

    void CharacterEntity::UpdateFocus() {
        focusedEntity = NULL;
        int numOverlappingObjects = actionObject->getNumOverlappingObjects();
        if (numOverlappingObjects) {
            for (int i = 0; i < numOverlappingObjects; i++) {
                VisibleEntity *entity = static_cast<VisibleEntity *>(actionObject->getOverlappingObject(i)->getUserPointer());
                if (entity && (entity != this)) {
                    focusedEntity = entity;
                    break;
                }
            }
        }
    }

    void CharacterEntity::UpdateBehaviour() {

        if (state & CS_IDLE) {
            bodyController->setWalkDirection(btVector3(0, 0, 0));
        }
        if (state & CS_MOVING_FORWARD) {                
            Ogre::Vector3 forward = node->getOrientation() * Ogre::Vector3::UNIT_Z;
            forward *= walkSpeed * (state & CS_RUNNING ? runFactor : 1.0);
//            float vely = body->getLinearVelocity().y();                
  //          forward.y = (vely < 0.0 ? vely : 0.0);        
            bodyController->setWalkDirection(Utils::OgreVec3ToBt(forward));
        }

        if (state & CS_TURNING_LEFT) {
            Ogre::Quaternion turn = Ogre::Vector3(0,0,1).getRotationTo(Ogre::Vector3(0.1, 0, 1));
            node->setOrientation(node->getOrientation() * turn);
        }
        if (state & CS_TURNING_RIGHT) {
            Ogre::Quaternion turn = Ogre::Vector3(0,0,1).getRotationTo(Ogre::Vector3(-0.1, 0, 1));
            node->setOrientation(node->getOrientation() * turn);
        }

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
            Utils::ClosestNotMeRayResultCallback(ghostObject);
        Core::GetInstance().bulWorld->rayTest(rayBegin, rayEnd, rayCallback);

        return rayCallback.hasHit();
    }
}

