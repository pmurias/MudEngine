#ifndef _MudEntityTemplateManager
#define _MudEntityTemplateManager

#include <MudHashmapManager.h>
#include <MudEntityTemplate.h>

namespace Mud {

    class EntityTemplateManager : public HashmapManager<EntityTemplate *> {
    public:

        EntityTemplateManager();

        EntityTemplate *getTemplate(const char *key);
    };
}

#endif

