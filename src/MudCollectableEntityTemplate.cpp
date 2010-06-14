#include <MudCollectableEntityTemplate.h>

namespace Mud {

    CollectableEntityTemplate::CollectableEntityTemplate() {
        type = ETT_COLLECTABLE;
        observable = true;
        collidable = true;
        dynamic = true;
        mass = 10.0;

        quantity = 1;
    }
}
