#ifndef _MudContainerEntityTemplate
#define _MudContainerEntityTemplate

#include <MudSceneryEntityTemplate.h>
#include <MudContainerEntityProperties.h>

namespace Mud {

	/**
	 * Template for creating container entity instances
	 */
    class ContainerEntityTemplate : public SceneryEntityTemplate, public ContainerEntityProperties {
    public:

        ContainerEntityTemplate();
    };
}

#endif

