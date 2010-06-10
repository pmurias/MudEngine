#ifndef _MudUtils
#define _MudUtils

#include <OGRE/Ogre.h>
#include <btBulletDynamicsCommon.h>

namespace Mud {

    class Utils {
    public:

        static void GetMeshInformation(
            const Ogre::MeshPtr mesh,
            size_t &vertex_count,
            Ogre::Vector3* &vertices,
            size_t &index_count,
            unsigned* &indices);

        static btVector3 OgreVec3ToBt(Ogre::Vector3 vec);
        static Ogre::Vector3 BtVec3ToOgre(btVector3 vec);

        static btQuaternion OgreQuatToBt(Ogre::Quaternion q);
        static Ogre::Quaternion BtQuatToOgre(btQuaternion q);

        class ClosestNotMeRayResultCallback : public btCollisionWorld::ClosestRayResultCallback
        {
        public:
            ClosestNotMeRayResultCallback (btCollisionObject* me) : 
                btCollisionWorld::ClosestRayResultCallback(btVector3(0.0, 0.0, 0.0), btVector3(0.0, 0.0, 0.0)) {
                    m_me = me;
            }
 
            virtual btScalar addSingleResult(btCollisionWorld::LocalRayResult& rayResult,bool normalInWorldSpace) {
                if (rayResult.m_collisionObject == m_me)
                    return 1.0;
                return ClosestRayResultCallback::addSingleResult (rayResult, normalInWorldSpace);
            }
        protected:
            btCollisionObject* m_me;
        };
    };
}

#endif
