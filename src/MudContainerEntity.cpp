#include <MudContainerEntity.h>
#include <MudContainerEntityTemplate.h>
#include <MudCore.h>

namespace Mud {

    ContainerEntity::ContainerEntity(const char *name, const char *entityTemplateName) 
        : SceneryEntity(name, entityTemplateName) {
        ContainerEntityTemplate *entTemplate = 
            static_cast<ContainerEntityTemplate*>(Core::GetInstance().entityTemplateManager.GetTemplate(entityTemplateName));

        *(static_cast<ContainerEntityProperties *>(this)) = *(static_cast<ContainerEntityProperties*>(entTemplate));
        observable = true;
    }

    ContainerEntity::~ContainerEntity() {
    }

    void ContainerEntity::Update() {        
        SceneryEntity::Update();
    }

    void ContainerEntity::SetPosition(Ogre::Vector3 pos) {
        SceneryEntity::SetPosition(pos);
    }

    void ContainerEntity::UpdatePosition() {
        SceneryEntity::UpdatePosition();
    }

    ActionType ContainerEntity::GetDefaultActionType() {
    	return AT_DEFAULT;
    }

}
