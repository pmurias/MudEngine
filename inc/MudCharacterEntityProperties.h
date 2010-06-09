#ifndef _MudCharacterEntityProperties
#define _MudCharacterEntityProperties

#include <OGRE/Ogre.h>

namespace Mud {

    class CharacterEntityProperties {
    public:
        float mass;
        float radius;
        float height;

        Ogre::Vector3 headOffset;        
    };
}

#endif

