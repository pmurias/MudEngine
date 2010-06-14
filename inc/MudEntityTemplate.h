#ifndef _MudEntityTemplate
#define _MudEntityTemplate

#include <string>
#include <MudEnums.h>

namespace Mud {

    /** Template for creating entities. Usually have same
     * properties as correlated entity, just without graphical
     * and physical engine objects. Used by EntityManager factory.
     */
    class EntityTemplate {
    public:

        EntityTemplateType type;

        EntityTemplate();
    };    
}

#endif

