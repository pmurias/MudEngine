#ifndef _MudCharacterEntity
#define _MudCharacterEntity

#include <MudVisibleEntity.h>
#include <MudCharacterEntityProperties.h>

namespace Mud {

    class CharacterEntity : public VisibleEntity, public CharacterEntityProperties {
    public:
        void Create(const char *name, const char *entityTemplateName);
        void Destroy();

        void SetPosition(Ogre::Vector3 pos);
        void UpdatePosition();
    };

}

#endif

