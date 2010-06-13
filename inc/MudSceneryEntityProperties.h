#ifndef _MudSceneryEntityProperties
#define _MudSceneryEntityProperties

#include <string>
#include <btBulletDynamicsCommon.h>
#include <OGRE/Ogre.h>

#include <MudEntityTemplate.h>
#include <MudEnums.h>

namespace Mud {

    /** Generic SceneryEntity field
     */
    class SceneryEntityProperties {
    public:
 
        /// Determine if physics body is used
        bool collidable;
        /// Determine if body is static (not dynamic)
        bool dynamic;
        /// Mass used when body is dynamic
        float mass;

        /// Bounding volume (Box, Sphere, Capsule)
        BoundingVolumeType boundingVolumeType;
        /// Bounding box size
        btVector3 boxSize;
        /// Sphere radius
        float radius;
        /// Capsule radius and height
        Ogre::Vector2 capsuleSize;

        SceneryEntityProperties();
    };
}

#endif

