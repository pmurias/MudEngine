#include <MudCharacterEntity.h>
#include <MudCharacterEntityTemplate.h>
#include <MudCharacterEntityProperties.h>
#include <MudCore.h>
#include <MudUtils.h>

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

        btDefaultMotionState *motionState = new btDefaultMotionState(
            btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0))
            );

        btVector3 inertia(0,0,0);

        collisionShape->calculateLocalInertia(entTemplate->mass, inertia);

        btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(
                entTemplate->mass, 
                motionState, 
                collisionShape, 
                inertia
            );

        body = new btRigidBody(rigidBodyCI);

        body->setDamping(0.5, 1.0);
        body->setActivationState(DISABLE_DEACTIVATION);
        body->setAngularFactor(btVector3(0,1,0));    

        Core::GetInstance().bulWorld->addRigidBody(body);
    }

    void CharacterEntity::Destroy() {
    }

    void CharacterEntity::Update() {
        UpdateBehaviour();
        UpdatePosition();
    }

    void CharacterEntity::SetPosition(Ogre::Vector3 pos) {
        node->setPosition(pos);
        body->translate(Utils::OgreVec3ToBt(pos) - body->getCenterOfMassPosition());
    }

    void CharacterEntity::UpdatePosition() {
        node->setPosition(Utils::BtVec3ToOgre(body->getCenterOfMassPosition()));
    }

    void CharacterEntity::UpdateBehaviour() {

        if (state & CS_IDLE) {
            body->setLinearVelocity(btVector3(0, body->getLinearVelocity().y(), 0));
        }
        if (state & CS_MOVING_FORWARD) {                
            Ogre::Vector3 forward = node->getOrientation() * Ogre::Vector3::UNIT_Z;
            forward *= walkSpeed * (state & CS_RUNNING ? runFactor : 1.0);
            float vely = body->getLinearVelocity().y();                
            forward.y = (vely < 0.0 ? vely : 0.0);
            body->setLinearVelocity(Utils::OgreVec3ToBt(forward));
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
            Utils::ClosestNotMeRayResultCallback(body);
        Core::GetInstance().bulWorld->rayTest(rayBegin, rayEnd, rayCallback);

        return rayCallback.hasHit();
    }
}

