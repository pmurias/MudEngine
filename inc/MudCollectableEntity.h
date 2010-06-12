#ifndef _MudCollectableEntity
#define _MudCollectableEntity

#include <MudSceneryEntity.h>

namespace Mud {

    class Item;

    /** Entity that can be picked up from the ground by the character
     */
    class CollectableEntity : public SceneryEntity {
    public:
        Item *item;

        CollectableEntity(const char *name, const char *entityTemplateName);
        void Destroy();

        void Update();

        void SetPosition(Ogre::Vector3 pos);
        void UpdatePosition();
    };

}

#endif
