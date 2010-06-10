#ifndef _MudCharacterEntityProperties
#define _MudCharacterEntityProperties

#include <OGRE/Ogre.h>

namespace Mud {

    class CharacterEntityProperties {
    public:
        float mass;
        float radius;
        float height;

        float walkSpeed;
        float runFactor;

        Ogre::Vector3 headOffset;
    };
}

#endif

