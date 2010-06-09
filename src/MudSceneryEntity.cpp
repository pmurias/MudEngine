#include <MudSceneryEntity.h>
#include <MudSceneryEntityTemplate.h>
#include <MudCore.h>
#include <MudUtils.h>

namespace Mud {

    void SceneryEntity::Create(const char *name, const char *entityTemplateName) {
        SceneryEntityTemplate *entTemplate = 
            static_cast<SceneryEntityTemplate*>(Core::GetInstance().entityTemplateManager.getTemplate(entityTemplateName));

        entity = Core::GetInstance().ogreSceneMgr->createEntity(name, entTemplate->meshName);
        node = Core::GetInstance().ogreSceneMgr->getRootSceneNode()->createChildSceneNode(name);
        node->attachObject(entity);

        if (entTemplate->collidable) {
            if (entTemplate->boundingVolumeType == BVT_BOX) {
                collisionShape = new btBoxShape(entTemplate->boxSize);
            } else if (entTemplate->boundingVolumeType == BVT_SPHERE) {
                collisionShape = new btSphereShape(entTemplate->radius);
            }

            btDefaultMotionState *motionState = new btDefaultMotionState(
                btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0))
                );

            ;
            btVector3 inertia(0,0,0);

            if (entTemplate->dynamic) {
                collisionShape->calculateLocalInertia(entTemplate->mass, inertia);
            }
            btRigidBody::btRigidBodyConstructionInfo rigidBodyCI(
                    entTemplate->mass, 
                    motionState, 
                    collisionShape, 
                    inertia
                );

            body = new btRigidBody(rigidBodyCI);
            Core::GetInstance().bulWorld->addRigidBody(body);

        }

    }

    void SceneryEntity::Destroy() {
    }

    void SceneryEntity::SetPosition(Ogre::Vector3 pos) {
        node->setPosition(pos);
        body->translate(Utils::OgreVec3ToBt(pos) - body->getCenterOfMassPosition());
    }

    void SceneryEntity::UpdatePosition() {
        node->setPosition(Utils::BtVec3ToOgre(body->getCenterOfMassPosition()));
        node->setOrientation(Utils::BtQuatToOgre(body->getOrientation()));
    }
}

