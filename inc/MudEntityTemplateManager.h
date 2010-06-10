#ifndef _MudEntityTemplateManager
#define _MudEntityTemplateManager

#include <MudHashmapManager.h>
#include <MudEntityTemplate.h>

namespace Mud {

    class EntityTemplateManager : public HashmapManager<EntityTemplate *> {
    public:

        EntityTemplateManager();

        EntityTemplate *GetTemplate(const char *key);
        void AddTemplate(const char *key, EntityTemplate *elem);
    };
}

#endif

