#ifndef _MudCharacterController
#define _MudCharacterController

#include <MudCharacterEntity.h>
#include <OGRE/Ogre.h>

namespace Mud {

    class CharacterController {
    public:
        CharacterEntity *character;
        VisibleEntity *focusedEntity;

        Ogre::Vector3 desiredCameraPosition;    
        Ogre::Vector3 cameraPositionNoCollision;
        float cameraDistance;
        float cameraReaction;
        float cameraHeight;

        CharacterController();
        void UpdateCameraPosition();
        void HandleInput();

        void HandleFocus();

    };
}

#endif

