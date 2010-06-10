#ifndef _MudVisibleEntity
#define _MudVisibleEntity

#include <OGRE/Ogre.h>
#include <btBulletDynamicsCommon.h>

#include <MudEntity.h>

namespace Mud {

    class VisibleEntity : public Entity {
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

