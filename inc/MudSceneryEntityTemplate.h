#ifndef _MudSceneryEntityTemplate
#define _MudSceneryEntityTemplate

#include <string>
#include <btBulletDynamicsCommon.h>

namespace Mud {

    class SceneryEntityTemplate : public EntityTemplate {

        bool collidable;        
        btVector3 boundingBoxSize;

        std::string meshName;

        void Init();
        
    };
}

#endif

