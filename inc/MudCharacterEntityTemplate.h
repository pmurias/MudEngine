#ifndef _MudCharacterEntityTemplate
#define _MudCharacterEntityTemplate

#include <string>
#include <btBulletDynamicsCommon.h>
#include <OGRE/Ogre.h>

#include <MudEntityTemplate.h>
#include <MudCharacterEntityProperties.h>
#include <MudEnums.h>

namespace Mud {

    class CharacterEntityTemplate : public EntityTemplate, public CharacterEntityProperties {
    public:
        std::string meshName;
    };
}

#endif

