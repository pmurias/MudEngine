#ifndef _MudItem
#define _MudItem

#include <MudEnums.h>
#include <MudItemProperties.h>

namespace Mud {

	class ItemTemplate;

    /** General game item 
     */
    class Item : public ItemProperties {
    public:
        /// Can be used i.e. for ammo or money
        int quantity;
        /// Template used to create this instance of Item
        ItemTemplate *itemTemplate;

        /// Returns new copy of an item
        Item *Clone();
    };
}


#endif
