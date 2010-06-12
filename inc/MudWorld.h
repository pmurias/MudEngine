#ifndef _MudWorld
#define _MudWorld

#include <OGRE/Ogre.h>
#include <btBulletDynamicsCommon.h>

namespace Mud {

    /** Game world 
     */
    class World {
    public:
        btCollisionShape *collisionShape;

        Ogre::Entity *entity;
        Ogre::SceneNode *node;

        /** Loads graphical world representation
         */
        void SetupWorldGraphics(const char *file);
        /** Loads physical world representation. It should be
         * modified version of the graphical representation. Can be i.e.
         * to create invisible walls, or to make stairs smooth
         */
        void SetupWorldPhysics(const char *file);
    };
}

#endif

