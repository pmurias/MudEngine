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
    	/// Angle of access, 0.0 to 360.0
    	float accessAngle;
 
        /// Collection of Item elements
        Inventory *inventory;

        ContainerEntityProperties();
    };

}

#endif

