#include <MudEntityTemplateManager.h>
#include <MudHashmapManager.h>
#include <cstdio>

namespace Mud {

    EntityTemplate *EntityTemplateManager::getTemplate(const char *key) {
        return getElement(key);
    }

}
