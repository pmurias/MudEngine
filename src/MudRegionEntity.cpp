#include <events/MudCharacterEnteredRegionEvent.h>
#include <MudCharacterEntity.h>
#include <MudRegionEntity.h>
#include <MudVisibleEntity.h>
#include <MudCore.h>
#include <MudUtils.h>

namespace Mud {

	RegionEntity::RegionEntity(const char *name, const char *meshName)
		: Entity(name, meshName) {
		Ogre::Entity *physicsEnt = Core::GetInstance().ogreSceneMgr->createEntity(name, meshName);

		size_t vertexCount, indexCount;
		Ogre::Vector3* vertices;
		unsigned* indices;

		Utils::GetMeshInformation(physicsEnt->getMesh(), vertexCount, vertices, indexCount, indices);
		btTriangleIndexVertexArray *vertexArray = new btTriangleIndexVertexArray(
			indexCount / 3,
			(int *)(indices),
			12,
			vertexCount,
			(btScalar *)(vertices),
			12
		);

		collisionShape = new btBvhTriangleMeshShape(vertexArray, true);

		btDefaultMotionState *levelMotionState = new btDefaultMotionState(
			btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0))
			);

		ghostObject = new btPairCachingGhostObject();
		ghostObject->setWorldTransform(btTransform(btQuaternion(0,0,0,1),btVector3(0,0,0)));
		ghostObject->setCollisionShape(collisionShape);
		ghostObject->setCollisionFlags(btCollisionObject::CF_NO_CONTACT_RESPONSE);

		Core::GetInstance().bulWorld->addCollisionObject(ghostObject,
				btBroadphaseProxy::SensorTrigger | btBroadphaseProxy::StaticFilter,
				btBroadphaseProxy::AllFilter);

		Core::GetInstance().ogreSceneMgr->destroyEntity(physicsEnt);

		callback = NULL;
	}
	RegionEntity::~RegionEntity() {

	}

	void RegionEntity::Update() {
		 int numOverlappingObjects = ghostObject->getNumOverlappingObjects();
		 for (int i = insideObjects.size() - 1; i >= 0; i--) {
			 int j;
			 for (j = 0; j < numOverlappingObjects; j++) {
				 if (static_cast<VisibleEntity*>(ghostObject->getOverlappingObject(j)->getUserPointer()) == insideObjects[i])
					 break;
			 }
			 if (j == numOverlappingObjects) {
				 insideObjects.erase(insideObjects.begin() + i);
			 }
		 }
		 if (numOverlappingObjects) {
			 for (int i = 0; i < numOverlappingObjects; i++) {
				 VisibleEntity *entity = static_cast<VisibleEntity*>(ghostObject->getOverlappingObject(i)->getUserPointer());
				 if (entity != NULL) {
					 unsigned int j;
					 for (j = 0; j < insideObjects.size(); j++) {
						 if  (entity == insideObjects[j]) break;
					 }
					 if (j == insideObjects.size()) {
						 insideObjects.push_back(entity);
						 if (dynamic_cast<CharacterEntity*>(entity) != NULL) {
							 Core::GetInstance().eventManager.QueueEvent(new CharacterEnteredRegionEvent(static_cast<CharacterEntity*>(entity), this));
						 }
					 }
				 }
			 }
		 }
	}
}
