#ifndef _MudSceneryEntityTemplate
#define _MudSceneryEntityTemplate

#include <string>
#include <btBulletDynamicsCommon.h>

#include <MudEntityTemplate.h>

namespace Mud {

    class SceneryEntityTemplate : public EntityTemplate {
    public:

        bool collidable;        
        bool dynamic;
        btVector3 boundingBoxSize;

        std::string meshName;

        SceneryEntityTemplate();
        
    };
}

#endif

