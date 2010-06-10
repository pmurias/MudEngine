#include <MudEntityManager.h>

namespace Mud {

    EntityManager::EntityManager() {
        managerName = "Entity Manager";
    }

    void EntityManager::AddEntity(Entity *elem) {
        AddSafeElement(elem->name.c_str(), elem);
    }

    void EntityManager::UpdateEntities() {
        for (typename Hashmap::iterator it = map.begin(); it != map.end(); it++) {
            it->second->Update();
        }
    }

}
