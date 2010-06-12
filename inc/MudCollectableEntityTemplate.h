#ifndef _MudCollectableEntityTemplate
#define _MudCollectableEntityTemplate

#include <MudSceneryEntityTemplate.h>

namespace Mud {

    class Item;

    class CollectableEntityTemplate : public SceneryEntityTemplate {
    public:
        Item *item;

        CollectableEntityTemplate();
    };
}

#endif

