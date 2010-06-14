#ifndef _MudItemFactory
#define _MudItemFactory

#include <MudHashmapManager.h>
#include <MudItemTemplate.h>

namespace Mud {

	class Item;

	/**
	 * Factory which manages ItemTemplate instances and
	 * creates Item instances
	 */
	class ItemFactory : public HashmapManager<ItemTemplate*> {
	public:
		/// Adds template with an unique name
		void AddItemTemplate(const char *name, ItemTemplate *temp);
		/// Retrieves template with name tempName
		ItemTemplate *GetItemTemplate(const char *tempName);

		/// Creates new instance of item with properties based on template
		Item *CreateItem(const char *tempName, int quantity = 1);
	};

};

#endif
