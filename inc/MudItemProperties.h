#ifndef _MudItemProperties
#define _MudItemProperties

#include <MudEnums.h>

namespace Mud {

	/**
	 * Properties common for Item and ItemTemplate
	 */
	class ItemProperties {
	public:
        /// Weight in inventory
        float weight;
        /// Trade value
        float value;
        /// Item class
        ItemClass itemClass;
	};

}

#endif
