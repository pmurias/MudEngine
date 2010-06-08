#ifndef _MudEntityTemplate
#define _MudEntityTemplate

#include <string>

namespace Mud {

    enum EntityTemplateType {
        ETT_NONE,
        ETT_SCENERY
    };

    class EntityTemplate {
    public:

        EntityTemplateType type;

        EntityTemplate();
    };    
}

#endif

