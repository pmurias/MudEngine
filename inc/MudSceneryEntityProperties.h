#ifndef _MudSceneryEntityProperties
#define _MudSceneryEntityProperties

#include <string>
#include <btBulletDynamicsCommon.h>
#include <OGRE/Ogre.h>

#include <MudEntityTemplate.h>
#include <MudVisibleEntityProperties.h>
#include <MudEnums.h>

namespace Mud {

    class SceneryEntityProperties : public VisibleEntityProperties {
    public:
        
        bool collidable;
        bool dynamic;
        float mass;
        BoundingVolumeType boundingVolumeType;
        btVector3 boxSize;
        float radius;
        Ogre::Vector2 capsuleSize;

        SceneryEntityProperties();
    };
}

#endif

