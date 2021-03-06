#include <MudInventory.h>
#include <MudItem.h>

namespace Mud {

    Inventory *Inventory::Clone() {
        Inventory *inventory = new Inventory();
        inventory->capacity = this->capacity;
        inventory->weight = this->weight;
        for (std::vector<Item*>::iterator it = items.begin(); it != items.end(); it++) {
            inventory->items.push_back((*it)->Clone());
        }
    }

    void Inventory::AddItem(Item *item) {
    	items.push_back(item);
    	weight += item->weight;
    }

    bool Inventory::IsOverweight() {
    	return weight > capacity;
    }

}
