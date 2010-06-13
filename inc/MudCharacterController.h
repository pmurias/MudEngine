#ifndef _MudCharacterController
#define _MudCharacterController

#include <MudCharacterEntity.h>
#include <OGRE/Ogre.h>

namespace Mud {

    /** Handles user - player CharacterEntity interaction 
     */
    class CharacterController {
    public:
        /// Player character
        CharacterEntity *character;        
        VisibleEntity *focusedEntity;

        /// Desired camera position (camera will smoothly move to this position)
        Ogre::Vector3 desiredCameraPosition;    
        /// Current position without raytesting
        Ogre::Vector3 cameraPositionNoCollision;
        /// Camera distance from player's head
        float cameraDistance;
        /// Determines how smooth camera will move (0.0 - no movement, 1.0 - instant movement)
        float cameraReaction;
        /// Camera up distance from player's head
        float cameraHeight;

        CharacterController();
        void UpdateCameraPosition();
        void HandleInput();

        void HandleFocus();

    };
}

#endif

