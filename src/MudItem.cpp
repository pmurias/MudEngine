#include <MudItem.h>

namespace Mud {

    Item *Item::Clone() {
        Item *item = new Item();
        item->weight = this->weight;
        item->value = this->value;
        item->itemClass = this->itemClass;
        item->quantity = this->quantity;

        return item;
    }
}
