#include <MudEntityTemplateManager.h>
#include <MudHashmapManager.h>
#include <MudException.h>
#include <cstdio>

namespace Mud {

    EntityTemplateManager::EntityTemplateManager() {
        managerName = "Template Manager";
    }

    EntityTemplate *EntityTemplateManager::getTemplate(const char *key) {
        return getSafeElement(key);
    }

    void EntityTemplateManager::addTemplate(const char *key, EntityTemplate *elem) {
        addSafeElement(key, elem);
    }

}
