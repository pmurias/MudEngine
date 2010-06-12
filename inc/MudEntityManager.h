#ifndef _MudEntityManager
#define _MudEntityManager

#include <MudHashmapManager.h>
#include <MudEntity.h>

namespace Mud {

    /** Manages, updates state of all entities existing in game
     */
    class EntityManager : public HashmapManager<Entity *> {
    public:

        EntityManager();

        void AddEntity(Entity *elem);

        void UpdateEntities();
    };
}

#endif
