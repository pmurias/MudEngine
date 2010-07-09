#ifndef _MudRegionEntity
#define _MudRegionEntity

#include <MudVisibleEntity.h>

#include <btBulletDynamicsCommon.h>
#include <BulletCollision/CollisionDispatch/btGhostObject.h>

#include <vector>

namespace Mud {

	class VisibleEntity;
	class LuaFunction;

	/**
	 * Represents game regions used to trigger various events
	 */
	class RegionEntity : public Entity {
	public:
		btPairCachingGhostObject *ghostObject;
		btCollisionShape *collisionShape;
		std::vector<VisibleEntity*> insideObjects;

		LuaFunction *callback;

		RegionEntity(const char *name, const char *meshName);
		~RegionEntity();

		void Update();
	};
}

#endif
