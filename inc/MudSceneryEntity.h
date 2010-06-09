#ifndef _MudSceneryEntity
#define _MudSceneryEntity

#include <MudVisibleEntity.h>
#include <MudSceneryEntityProperties.h>

namespace Mud {

    class SceneryEntity : public VisibleEntity, public SceneryEntityProperties {
    public:
        void Create(const char *name, const char *entityTemplateName);
        void Destroy();

        void SetPosition(Ogre::Vector3 pos);
        void UpdatePosition();
    };

}

#endif

