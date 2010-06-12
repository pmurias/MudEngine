#ifndef _MudInventory
#define _MudInventory

namespace Mud {

    /** Collection of CollectableEntity used as
     * characters or container inventory
     */
    class Inventory {
    public:
    
        float capacity;
        Inventory *Clone();
    };
}

#endif

