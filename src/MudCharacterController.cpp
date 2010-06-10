#include <MudCharacterController.h>
#include <MudCore.h>
#include <MudException.h>

namespace Mud {

    CharacterController::CharacterController() {
        character = NULL;
    }

    void CharacterController::UpdateCameraPosition() {
        if (character) {
            desiredCameraPosition = character->node->getPosition();
            Ogre::Vector3 backward = character->node->getOrientation() * (-Ogre::Vector3::UNIT_Z);
            backward *= cameraDistance;
            Ogre::Vector3 upward = character->headOffset + Ogre::Vector3(0,cameraHeight,0);

            desiredCameraPosition += backward + upward;
            Ogre::Vector3 currentPosition = Core::GetInstance().ogreCamera->getPosition();

            Core::GetInstance().ogreCamera->setPosition(
                currentPosition +
                (desiredCameraPosition - currentPosition) * cameraReaction
                );

            Core::GetInstance().ogreCamera->lookAt(character->node->getPosition() + character->headOffset);
        }
    }

    void CharacterController::HandleInput() {
        if (Core::GetInstance().oisKeyboard->isKeyDown(OIS::KC_UP)) {
            character->StartMovingForward();
        } else {
            character->StopMoving();
        }

        if (Core::GetInstance().oisKeyboard->isKeyDown(OIS::KC_LEFT)) {
            character->TurnLeft();
        } else
        if (Core::GetInstance().oisKeyboard->isKeyDown(OIS::KC_RIGHT)) {
            character->TurnRight();
        } else {
            character->StopTurning();
        }

        if (Core::GetInstance().oisKeyboard->isKeyDown(OIS::KC_LSHIFT)) {
            character->Run();
        } else {
            character->Walk();
        }
    }

}
