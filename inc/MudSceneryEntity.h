#ifndef _MudSceneryEntity
#define _MudSceneryEntity

#include <MudVisibleEntity.h>
#include <MudSceneryEntityProperties.h>

namespace Mud {

    class SceneryEntity : public VisibleEntity, public SceneryEntityProperties {
    public:
        SceneryEntity(const char *name, const char *entityTemplateName);
        ~SceneryEntity();

        void Update();

        void SetPosition(Ogre::Vector3 pos);
        void UpdatePosition();
        void ActionPerform(Action *action);

        ActionType GetDefaultActionType();
    };

}

#endif

