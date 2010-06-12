#ifndef _MudItem
#define _MudItem

#include <MudEnums.h>

namespace Mud {

    /** General game item 
     */
    class Item {
    public:
        /// Weight in inventory
        float weight;
        /// Trade value
        float value;
        /// Can be used i.e. for ammo or money
        int quantity;
                
        ItemClass itemClass;

        /// Returns new copy of an item
        Item *Clone();
    };
}

#endif
