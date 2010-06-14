#ifndef _MudEntityManager
#define _MudEntityManager

#include <MudHashmapManager.h>
#include <MudEntity.h>
#include <list>

namespace Mud {

    /** Manages, updates state of all entities existing in game
     */
    class EntityManager : public HashmapManager<Entity *> {
    public:
    	std::list<std::string> destructionQueue;

        EntityManager();

        void AddEntity(Entity *elem);
        void QueueToDestroy(Entity *elem);

        void UpdateEntities();
    };
}

#endif
