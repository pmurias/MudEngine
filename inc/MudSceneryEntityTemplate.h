#ifndef _MudSceneryEntityTemplate
#define _MudSceneryEntityTemplate

#include <string>
#include <btBulletDynamicsCommon.h>
#include <OGRE/Ogre.h>

#include <MudEntityTemplate.h>
#include <MudEnums.h>

namespace Mud {

    class SceneryEntityTemplate : public EntityTemplate {
    public:

        bool collidable;        
        bool dynamic;
        float mass;
        BoundingVolumeType boundingVolumeType;
        btVector3 boxSize;
        float radius;
        Ogre::Vector2 capsuleSize;

        std::string meshName;

        SceneryEntityTemplate();
        
    };
}

#endif

