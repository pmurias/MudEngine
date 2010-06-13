#ifndef _MudInventory
#define _MudInventory

#include <vector>

namespace Mud {

    class Item;

    /** Collection of CollectableEntity used as
     * characters or container inventory
     */
    class Inventory {
    public:
        /// Collection of items
        std::vector<Item *> items;
        /// Maximum inventory capacity
        float capacity;
        /// Weight of current items
        float weight;

        /// Returns copy of Inventory object and all items it contains
        Inventory *Clone();        
    };
}

#endif

