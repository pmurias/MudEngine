#include <MudWorld.h>
#include <MudCore.h>
#include <MudUtils.h>

namespace Mud {

    Core &core = Core::GetInstance();

    void World::SetupWorldGraphics(char *file) {
        entity = core.ogreSceneMgr->createEntity("MudWorldEntity", file);
        node = core.ogreSceneMgr->getRootSceneNode()->createChildSceneNode("MudWorldNode");
        node->attachObject(entity);
    }

    void World::SetupWorldPhysics(char *file) {
        Ogre::Entity *physicsEnt = core.ogreSceneMgr->createEntity("PhysicsEntity", file);

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

        btRigidBody::btRigidBodyConstructionInfo
            levelRigidBodyCI(0, levelMotionState, collisionShape, btVector3(0,0,0));
        btRigidBody* body = new btRigidBody(levelRigidBodyCI);

        core.bulWorld->addRigidBody(body);
    }

}
