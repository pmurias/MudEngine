#ifndef _MudCollectableEntityTemplate
#define _MudCollectableEntityTemplate

#include <MudSceneryEntityTemplate.h>
#include <string>

namespace Mud {

    class ItemTemplate;

    /**
     * Template for creating collectible entities
     */
    class CollectableEntityTemplate : public SceneryEntityTemplate {
    public:
    	std::string itemTemplateName;
    	int quantity;

        CollectableEntityTemplate();
    };
}

#endif

