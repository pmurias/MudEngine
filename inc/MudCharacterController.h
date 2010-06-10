#ifndef _MudCharacterController
#define _MudCharacterController

#include <MudCharacterEntity.h>
#include <OGRE/Ogre.h>

namespace Mud {

    class CharacterController {
    public:
        CharacterEntity *character;

        Ogre::Vector3 desiredCameraPosition;    
        float cameraDistance;
        float cameraReaction;
        float cameraHeight;

        CharacterController();
        void UpdateCameraPosition();
        void HandleInput();

    };
}

#endif

