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

    };
}

#endif
