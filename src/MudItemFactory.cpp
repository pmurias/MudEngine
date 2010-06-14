#include <MudItemFactory.h>
#include <MudItemProperties.h>
#include <MudItem.h>

namespace Mud {

	void ItemFactory::AddItemTemplate(const char *key, ItemTemplate *elem) {
		AddSafeElement(key, elem);
	}

	ItemTemplate *ItemFactory::GetItemTemplate(const char *key) {
		return GetSafeElement(key);
	}

	Item *ItemFactory::CreateItem(const char *tempName, int quantity) {
		ItemTemplate *temp = GetItemTemplate(tempName);

		Item *item = new Item();
		*(static_cast<ItemProperties*>(item)) = *(static_cast<ItemProperties*>(temp));
		item->quantity = quantity;

		return item;
	}
}
