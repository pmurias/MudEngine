#ifndef _MudCharacterEntityProperties
#define _MudCharacterEntityProperties

#include <OGRE/Ogre.h>

namespace Mud {

    /** Generic character properties
     */
    class CharacterEntityProperties {
    public:
        /// Used by physics engine
        float mass;
        /// Bounding capsule radius
        float radius;
        /// Bounding capsule height
        float height;

        /// Walk speed (units per frame)
        float walkSpeed;
        /// Factor that walk speed get multiplied by when character is running
        float runFactor;

        /// Head offset from center of mass position. Used by CharacterController.
        Ogre::Vector3 headOffset;        
    };
}

#endif

