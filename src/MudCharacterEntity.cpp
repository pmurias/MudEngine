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

        entity = Core::GetInstance().ogreSceneMgr->createEntity(name, entTemplate->meshName);
        node = Core::GetInstance().ogreSceneMgr->getRootSceneNode()->createChildSceneNode(name);
        node->attachObject(entity);

        collisionShape = new btCapsuleShape(entTemplate->radius, entTemplate->height);

        ghostObject = new btPairCachingGhostObject();
        ghostObject->setWorldTransform(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));
        
        Core::GetInstance().bulBroadphase->getOverlappingPairCache()->setInternalGhostPairCallback(new btGhostPairCallback());

        ghostObject->setCollisionShape(collisionShape);
        ghostObject->setCollisionFlags(btCollisionObject::CF_CHARACTER_OBJECT);
        ghostObject->setUserPointer(this);

        bodyController = new btKinematicCharacterController(ghostObject, (btConvexShape*)(collisionShape), 0.2);

        Core::GetInstance().bulWorld->addCollisionObject(
            ghostObject, 
            btBroadphaseProxy::DefaultFilter, 
            btBroadphaseProxy::StaticFilter |
            btBroadphaseProxy::DefaultFilter);
        Core::GetInstance().bulWorld->addAction(bodyController);
    }

    void CharacterEntity::Destroy() {
    }

    void CharacterEntity::Update() {
        UpdateBehaviour();
        UpdatePosition();
    }

    void CharacterEntity::SetPosition(Ogre::Vector3 pos) {
        bodyController->warp(Utils::OgreVec3ToBt(pos));
    }

    void CharacterEntity::UpdatePosition() {
        node->setPosition(Utils::BtVec3ToOgre(ghostObject->getWorldTransform().getOrigin()));
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

