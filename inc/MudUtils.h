#ifndef _MudUtils
#define _MudUtils

#include <OGRE/Ogre.h>

namespace Mud {

    class Utils {
    public:

        static void GetMeshInformation(
            const Ogre::MeshPtr mesh,
            size_t &vertex_count,
            Ogre::Vector3* &vertices,
            size_t &index_count,
            unsigned* &indices);

    };
}

#endif
