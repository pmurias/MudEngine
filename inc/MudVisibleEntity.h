#ifndef _MudVisibleEntity
#define _MudVisibleEntity

#include <MudEntity.h>
#include <MudVisibleEntityProperties.h>

#include <OGRE/Ogre.h>
#include <btBulletDynamicsCommon.h>


namespace Mud {

    class VisibleEntity : public Entity, public VisibleEntityProperties {
    public:
        Ogre::Entity *entity;
        Ogre::SceneNode *node;

        btRigidBody *body;
        btCollisionShape *collisionShape;

        VisibleEntity(const char *name, const char *entityTemplateName);
        virtual void Destroy();

        virtual void SetPosition(Ogre::Vector3 pos);
        virtual void UpdatePosition();

        virtual void Update();
    };

}

#endif

