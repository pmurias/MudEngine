#include <MudSceneryEntityProperties.h>

namespace Mud {

    SceneryEntityProperties::SceneryEntityProperties() 
        : VisibleEntityProperties() {
        collidable = false;
        dynamic = false;
    }
}
