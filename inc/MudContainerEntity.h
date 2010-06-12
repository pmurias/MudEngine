#ifndef _MudContainerEntity
#define _MudContainerEntity

#include <MudSceneryEntity.h>
#include <MudContainerEntityProperties.h>

namespace Mud {

    class ContainerEntity : public SceneryEntity, public ContainerEntityProperties {
    public:
        ContainerEntity(const char *name, const char *entityTemplateName);
        void Destroy();

        void Update();

        void SetPosition(Ogre::Vector3 pos);
        void UpdatePosition();

    };

}

#endif

