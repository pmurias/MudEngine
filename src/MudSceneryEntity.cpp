#include <MudSceneryEntity.h>
#include <MudSceneryEntityTemplate.h>
#include <MudCore.h>
#include <MudUtils.h>

namespace Mud {

    SceneryEntity::SceneryEntity(const char *name, const char *entityTemplateName) 
        : VisibleEntity(name, entityTemplateName) {
        SceneryEntityTemplate *entTemplate = 
            static_cast<SceneryEntityTemplate*>(Core::GetInstance().entityTemplateManager.GetTemplate(entityTemplateName));

        *(static_cast<SceneryEntityProperties *>(this)) = *(static_cast<SceneryEntityProperties*>(entTemplate));

        entity = Core::GetInstance().ogreSceneMgr->createEntity(name, entTemplate->meshName);
        node = Core::GetInstance().ogreSceneMgr->getRootSceneNode()->createChildSceneNode(name);
        node->attachObject(entity);

        if (collidable) {
            if (boundingVolumeType == BVT_BOX) {
                collisionShape = new btBoxShape(boxSize);
            } else if (boundingVolumeType == BVT_SPHERE) {
                collisionShape = new btSphereShape(radius);
            }

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
            Core::GetInstance().bulWorld->addRigidBody(body);
        }

    }

    void SceneryEntity::Destroy() {
    }

    void SceneryEntity::Update() {
        UpdatePosition();
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

