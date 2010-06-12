#ifndef _MudVisibleEntityProperties
#define _MudVisibleEntityProperties

#include <string>

namespace Mud {

    /** Bunch of properties that are common in VisibleEntity and VisibleEntityTemplate
     */
    class VisibleEntityProperties {
    public:
        /// In-game entity name
        std::string displayName;
        /// Determines if player can focus action on entity
        bool observable;

        VisibleEntityProperties();
    };
}

#endif

