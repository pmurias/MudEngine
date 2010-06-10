#ifndef _MudVisibleEntityProperties
#define _MudVisibleEntityProperties

#include <string>

namespace Mud {

    class VisibleEntityProperties {
    public:
        std::string displayName;
        bool observable;

        VisibleEntityProperties();
    };
}

#endif

