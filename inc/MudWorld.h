#ifndef _MudWorld
#define _MudWorld

#include <OGRE/Ogre.h>
#include <btBulletDynamicsCommon.h>

namespace Mud {

    class World {
    public:
        btCollisionShape *collisionShape;

        Ogre::Entity *entity;
        Ogre::SceneNode *node;

        void SetupWorldGraphics(char *file);
        void SetupWorldPhysics(char *file);
    };
}

#endif

