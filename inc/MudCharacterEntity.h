#ifndef _MudCharacterEntity
#define _MudCharacterEntity

#include <MudVisibleEntity.h>
#include <MudCharacterEntityProperties.h>
#include <MudEnums.h>

namespace Mud {

    class CharacterEntity : public VisibleEntity, public CharacterEntityProperties {
    public:
        int state;

        CharacterEntity(const char *name, const char *entityTemplateName);
        void Destroy();

        void Update();

        void SetPosition(Ogre::Vector3 pos);
        void UpdatePosition();
        void UpdateBehaviour();

        void StartMovingForward();
        void TurnLeft();
        void TurnRight();
        void StopMoving();
        void StopTurning();
        void Run();
        void Walk();

    };

}

#endif

