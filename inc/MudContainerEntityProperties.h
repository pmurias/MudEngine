#ifndef _MudContainerEntityProperties
#define _MudContainerEntityProperties

#include <MudSceneryEntityProperties.h>
#include <MudInventory.h>

namespace Mud {

    /** Generic container object properties
     */
    class ContainerEntityProperties {
    public:
    	/// Determines if container is locked
    	bool isLocked;
 
        /// Collection of Item elements
        Inventory *inventory;

        ContainerEntityProperties();
    };

}

#endif

