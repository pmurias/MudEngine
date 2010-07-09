#include <MudCharacterController.h>
#include <MudCore.h>
#include <MudException.h>
#include <MudUtils.h>

namespace Mud {

    CharacterController::CharacterController() {
        character = NULL;
        focusedEntity = NULL;
    }


    void CharacterController::UpdateCameraPosition() {
        if (character) {
            desiredCameraPosition = character->node->getPosition();
            Ogre::Vector3 backward = character->node->getOrientation() * (-Ogre::Vector3::UNIT_Z);
            backward *= cameraDistance;
            Ogre::Vector3 upward = character->headOffset + Ogre::Vector3(0,cameraHeight,0);

            desiredCameraPosition += backward + upward;        
            Ogre::Vector3 currentPosition = Core::GetInstance().ogreCamera->getPosition();

            cameraPositionNoCollision = 
                cameraPositionNoCollision +
                (desiredCameraPosition - cameraPositionNoCollision) * cameraReaction;

            btVector3 rayBegin = Utils::OgreVec3ToBt(character->node->getPosition() + character->headOffset);
            btVector3 rayEnd = Utils::OgreVec3ToBt(cameraPositionNoCollision);
            Utils::ClosestNotMeRayResultCallback rayCallback = 
                Utils::ClosestNotMeRayResultCallback(character->body);
            Core::GetInstance().bulWorld->rayTest(rayBegin, rayEnd, rayCallback);

            float fraction = 0.9f * (rayCallback.hasHit() ? (rayCallback.m_closestHitFraction) : 1.0f);

            Ogre::Vector3 cameraPosition = Utils::BtVec3ToOgre(
				rayBegin + (rayEnd - rayBegin) * fraction
			);


            Core::GetInstance().ogreCamera->setPosition(cameraPosition);
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
            character->StartTurningLeft();
        } else
        if (Core::GetInstance().oisKeyboard->isKeyDown(OIS::KC_RIGHT)) {
            character->StartTurningRight();
        } else {
            character->StopTurning();
        }

        if (Core::GetInstance().oisKeyboard->isKeyDown(OIS::KC_LSHIFT)) {
            character->StartRunning();
        } else {
            character->StartWalking();
        }

        if (Core::GetInstance().oisKeyboard->isKeyDown(OIS::KC_LCONTROL)) {
        	character->PerfromDefaultActionOnFocusedEntity();
        }
    }

    void CharacterController::HandleFocus() {
        focusedEntity = character->focusedEntity;
    }

    

}
