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
            body->setDamping(0.9, 0.99);
            body->setFriction(0.9);

            body->setUserPointer(static_cast<void *>(this));
            Core::GetInstance().bulWorld->addRigidBody(body);
        }

    }

    SceneryEntity::~SceneryEntity() {
    	node->detachAllObjects();
    	Core::GetInstance().ogreSceneMgr->destroySceneNode(node);
    	Core::GetInstance().ogreSceneMgr->destroyEntity(entity);

    	if (collidable) {
    		Core::GetInstance().bulWorld->removeRigidBody(body);
    		delete body->getMotionState();
    		delete body;
    		delete collisionShape;
    	}
    }

    void SceneryEntity::Update() {
        UpdatePosition();
    }

    void SceneryEntity::SetPosition(Ogre::Vector3 pos) {
        node->setPosition(pos);
        if (collidable)
        	body->translate(Utils::OgreVec3ToBt(pos) - body->getCenterOfMassPosition());
    }

    void SceneryEntity::UpdatePosition() {
    	if (collidable) {
    		node->setPosition(Utils::BtVec3ToOgre(body->getCenterOfMassPosition()));
    		node->setOrientation(Utils::BtQuatToOgre(body->getOrientation()));
    	}
    }

    void SceneryEntity::ActionPerform(Action *action) {
    }

    ActionType SceneryEntity::GetDefaultActionType() {
    	return AT_DEFAULT;
    }
}

