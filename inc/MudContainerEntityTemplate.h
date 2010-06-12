#ifndef _MudContainerEntityTemplate
#define _MudContainerEntityTemplate

#include <MudSceneryEntityTemplate.h>
#include <MudContainerEntityProperties.h>

namespace Mud {

    class ContainerEntityTemplate : public SceneryEntityTemplate, public ContainerEntityProperties {
    public:

        ContainerEntityTemplate();
    };
}

#endif

