#ifndef _MudSceneryEntity
#define _MudSceneryEntity

#include <MudVisibleEntity.h>

namespace Mud {

    class SceneryEntity : public VisibleEntity {
    public:
        void Create(char *name, char *entityTemplateName);
        void Destroy();
    };

}

#endif

