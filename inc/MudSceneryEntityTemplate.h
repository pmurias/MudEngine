#ifndef _MudSceneryEntityTemplate
#define _MudSceneryEntityTemplate

#include <string>
#include <btBulletDynamicsCommon.h>
#include <OGRE/Ogre.h>

#include <MudEntityTemplate.h>
#include <MudSceneryEntityProperties.h>
#include <MudEnums.h>

namespace Mud {

    class SceneryEntityTemplate : public EntityTemplate, public SceneryEntityProperties {
    public:
        std::string meshName;

        SceneryEntityTemplate();
        
    };
}

#endif

