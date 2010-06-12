#ifndef _MudVisibleEntityTemplate
#define _MudVisibleEntityTemplate

#include <MudEntityTemplate.h>
#include <MudVisibleEntityProperties.h>

namespace Mud {
    
    class VisibleEntityTemplate : public EntityTemplate, public VisibleEntityProperties {
    public:

        int usersCount;
    };
}

#endif

