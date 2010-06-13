#ifndef _MudCharacterEntity
#define _MudCharacterEntity

#include <MudVisibleEntity.h>
#include <MudCharacterEntityProperties.h>
#include <MudEnums.h>

#include <BulletDynamics/Character/btKinematicCharacterController.h>

namespace Mud {

    class CharacterEntity : public VisibleEntity, public CharacterEntityProperties {
    public:
        VisibleEntity *focusedEntity;
        int state;
        btKinematicCharacterController *bodyController;
        btPairCachingGhostObject *ghostObject;
        btConvexShape *actionCollisionShape;
        btPairCachingGhostObject *actionObject;

        CharacterEntity(const char *name, const char *entityTemplateName);
        void Destroy();

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

    };

}

#endif

