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

        virtual void Create(char *name, char *entityTemplateName);
        virtual void Destroy();
    };

}

#endif

