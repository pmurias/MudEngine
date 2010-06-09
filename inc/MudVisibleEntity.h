#ifndef _MudVisibleEntity
#define _MudVisibleEntity

#include <OGRE/Ogre.h>
#include <btBulletDynamicsCommon.h>

namespace Mud {

    class VisibleEntity {
    public:
        Ogre::Entity *entity;
        Ogre::SceneNode *node;

        btRigidBody *body;
        btCollisionShape *collisionShape;

        virtual void Create(const char *name, const char *entityTemplateName);
        virtual void Destroy();

        virtual void SetPosition(Ogre::Vector3 pos);
        virtual void UpdatePosition();
    };

}

#endif

