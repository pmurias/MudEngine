#ifndef _MudEntityManager
#define _MudEntityManager

#include <MudHashmapManager.h>
#include <MudEntity.h>
#include <vector>

namespace Mud {

    /** Manages, updates state of all entities existing in game
     */
    class EntityManager : public HashmapManager<Entity *> {
    public:
    	std::vector<std::string> destructionQueue;

        EntityManager();

        void AddEntity(Entity *elem);
        void QueueToDestroy(Entity *elem);
        bool IsQueuedToDestroy(Entity *elem);

        void UpdateEntities();
    };
}

#endif
