#ifndef _MudContainerEntityProperties
#define _MudContainerEntityProperties

#include <MudSceneryEntityProperties.h>
#include <MudInventory.h>

namespace Mud {

    class ContainerEntityProperties {
    public:
    
        Inventory *inventory;

        ContainerEntityProperties();
    };

}

#endif

