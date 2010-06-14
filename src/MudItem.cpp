#include <MudItem.h>
#include <MudCore.h>

namespace Mud {

    Item *Item::Clone() {
        Item *item = Core::GetInstance().itemFactory.CreateItem(itemTemplate->name.c_str());
        item->quantity = this->quantity;

        return item;
    }
}
