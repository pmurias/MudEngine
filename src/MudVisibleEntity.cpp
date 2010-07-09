#include <MudVisibleEntity.h>
#include <MudVisibleEntityTemplate.h>
#include <MudCore.h>

namespace Mud {

    VisibleEntity::VisibleEntity(const char *name, const char *entityTemplateName)
        : Entity(name, entityTemplateName) {
        VisibleEntityTemplate *entTemplate = 
            static_cast<VisibleEntityTemplate*>(Core::GetInstance().entityTemplateManager.GetTemplate(entityTemplateName));     

        *(static_cast<VisibleEntityProperties *>(this)) = *(static_cast<VisibleEntityProperties*>(entTemplate));
    }

    VisibleEntity::~VisibleEntity() {

    }


    void VisibleEntity::SetPosition(Ogre::Vector3 pos) {

    }

    void VisibleEntity::UpdatePosition() {
    }

    void VisibleEntity::Update() {
    }


    ActionType VisibleEntity::GetDefaultActionType() {
    	return AT_DEFAULT;
    }

}

