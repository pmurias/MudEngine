#include <MudEntityTemplateManager.h>
#include <MudHashmapManager.h>
#include <MudException.h>
#include <cstdio>

namespace Mud {

    EntityTemplateManager::EntityTemplateManager() {
        managerName = "Template Manager";
    }

    EntityTemplate *EntityTemplateManager::GetTemplate(const char *key) {
        return GetSafeElement(key);
    }

    void EntityTemplateManager::AddTemplate(const char *key, EntityTemplate *elem) {
        AddSafeElement(key, elem);
    }

}
