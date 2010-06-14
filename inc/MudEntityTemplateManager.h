#ifndef _MudEntityTemplateManager
#define _MudEntityTemplateManager

#include <MudHashmapManager.h>
#include <MudEntityTemplate.h>

namespace Mud {

	/**
	 * It Manages all templates. It is not a Entity factory
	 */
    class EntityTemplateManager : public HashmapManager<EntityTemplate *> {
    public:

        EntityTemplateManager();

        EntityTemplate *GetTemplate(const char *key);
        void AddTemplate(const char *key, EntityTemplate *elem);
    };
}

#endif

