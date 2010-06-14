#ifndef _MudItemTemplate
#define _MudItemTemplate

#include <string>
#include <MudItemProperties.h>

namespace Mud {

	/**
	 * Template for creating Item instances,
	 * managed by ItemFactory
	 */
	class ItemTemplate : public ItemProperties {
	public:

		/// Display name of the item
		std::string name;

		/// Description of the item
		std::string description;
	};

}

#endif
