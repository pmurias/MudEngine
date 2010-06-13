#ifndef _MudContainerEntityProperties
#define _MudContainerEntityProperties

#include <MudSceneryEntityProperties.h>
#include <MudInventory.h>

namespace Mud {

    /** Generic container object properties
     */
    class ContainerEntityProperties {
    public:
 
        /// Collection of Item elements
        Inventory *inventory;

        ContainerEntityProperties();
    };

}

#endif

