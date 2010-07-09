#ifndef _MudCharacterEntity
#define _MudCharacterEntity

#include <MudVisibleEntity.h>
#include <MudCharacterEntityProperties.h>
#include <MudEnums.h>

#include <BulletDynamics/Character/btKinematicCharacterController.h>

namespace Mud {

	class Inventory;
	class Item;
	class CollectableEntity;
	class OpenableContainerEntity;
	class CharacterAnimationBlender;

	/**
	 * Game character class
	 */
    class CharacterEntity : public VisibleEntity, public CharacterEntityProperties {
    public:
    	CharacterAnimationBlender *animationBlender;

        VisibleEntity *focusedEntity;
        int generalState;
        int turningState;
        int walkingState;
        btPairCachingGhostObject *ghostObject;
        btConvexShape *ghostShape;
        btVector3 desiredMoveVelocity;

        CollectableEntity *pickingParam;
        int pickingPhase;

        OpenableContainerEntity *openCloseParam;

        CharacterEntity(const char *name, const char *entityTemplateName);
        ~CharacterEntity();

        void Update();

        void SetPosition(Ogre::Vector3 pos);
        void UpdatePosition();
        /// Updates information about entities in character's focus
        void UpdateFocus();

        /// Updates AI and state changes
        void UpdateBehaviour();

        void StartMovingForward();
        void StartTurningLeft();
        void StartTurningRight();
        void StopMoving();
        void StopTurning();
        void StartRunning();
        void StartWalking();
        void StartPicking(CollectableEntity *target);
        bool IsOnGround();
        void StartOpening(OpenableContainerEntity *target);
        void StartClosing(OpenableContainerEntity *target);
        void LookAt(VisibleEntity *target);

        /// Picks item into inventory
        void Pick(Item *item);

        /// Performs default action on entity in focus area of character
        void PerfromDefaultActionOnFocusedEntity();

        /// For character, default action is talk
        ActionType GetDefaultActionType();
    };

}

#endif

