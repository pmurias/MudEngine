#ifndef _MudCharacterEntity
#define _MudCharacterEntity

#include <MudVisibleEntity.h>
#include <MudCharacterEntityProperties.h>
#include <MudEnums.h>

#include <BulletDynamics/Character/btKinematicCharacterController.h>

namespace Mud {

	class Inventory;
	class Item;

	/**
	 * Game character class
	 */
    class CharacterEntity : public VisibleEntity, public CharacterEntityProperties {
    public:
        VisibleEntity *focusedEntity;
        int state;
        btPairCachingGhostObject *ghostObject;
        btConvexShape *ghostShape;
        btVector3 desiredMoveVelocity;

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
        void TurnLeft();
        void TurnRight();
        void StopMoving();
        void StopTurning();
        void Run();
        void Walk();
        bool IsOnGround();

        /// Picks item into inventory
        void Pick(Item *item);

        /// Performs default action on entity in focus area of character
        void PerfromDefaultActionOnFocusedEntity();

        /// For character, default action is talk
        ActionType GetDefaultActionType();

    };

}

#endif

