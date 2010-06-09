#include <MudCharacterEntity.h>
#include <MudCharacterEntityTemplate.h>
#include <MudCharacterEntityProperties.h>
#include <MudCore.h>
#include <MudUtils.h>

namespace Mud {

    void CharacterEntity::Create(const char *name, const char *entityTemplateName) {
        CharacterEntityTemplate *entTemplate = 
            static_cast<CharacterEntityTemplate*>(Core::GetInstance().entityTemplateManager.getTemplate(entityTemplateName));     

        *(static_cast<CharacterEntityProperties *>(this)) = *(static_cast<CharacterEntityProperties*>(entTemplate));

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

    void CharacterEntity::SetPosition(Ogre::Vector3 pos) {
        node->setPosition(pos);
        body->translate(Utils::OgreVec3ToBt(pos) - body->getCenterOfMassPosition());
    }

    void CharacterEntity::UpdatePosition() {
        node->setPosition(Utils::BtVec3ToOgre(body->getCenterOfMassPosition()));
    }
}

