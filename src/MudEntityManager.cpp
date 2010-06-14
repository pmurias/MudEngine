#include <MudEntityManager.h>
#include <MudCore.h>

namespace Mud {

    EntityManager::EntityManager() {
        managerName = "Entity Manager";
    }

    void EntityManager::AddEntity(Entity *elem) {
        AddSafeElement(elem->name.c_str(), elem);
    }

    void EntityManager::QueueToDestroy(Entity *elem) {
    	destructionQueue.push_back(elem->name);
    }

    void EntityManager::UpdateEntities() {
    	while (destructionQueue.size()) {
    		Entity *ent = map[destructionQueue.front()];
    		RemoveElement(destructionQueue.front().c_str());
    		destructionQueue.pop_front();
    		delete ent;
    	}

        for (typename Hashmap::iterator it = map.begin(); it != map.end(); it++) {
            it->second->Update();
        }

    }

}
