#ifndef _MudEntityTemplate
#define _MudEntityTemplate

#include <string>

namespace Mud {

    enum EntityTemplateType {
        ETT_NONE
    };

    class EntityTemplate {
    public:

        EntityTemplateType type;
    };
}

#endif

