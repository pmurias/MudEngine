#include <MudCollectableEntity.h>
#include <MudCollectableEntityTemplate.h>
#include <MudItem.h>
#include <MudCore.h>

namespace Mud {

    CollectableEntity::CollectableEntity(const char *name, const char *entityTemplateName) 
        : SceneryEntity(name, entityTemplateName) {
        CollectableEntityTemplate *entTemplate = 
            static_cast<CollectableEntityTemplate*>(Core::GetInstance().entityTemplateManager.GetTemplate(entityTemplateName));

        *(static_cast<SceneryEntityProperties *>(this)) = *(static_cast<SceneryEntityProperties*>(entTemplate));
        if (entTemplate->itemTemplateName != "") {
            item = Core::GetInstance().itemFactory.CreateItem(entTemplate->itemTemplateName.c_str(), entTemplate->quantity);
            displayName = Core::GetInstance().itemFactory.GetItemTemplate(entTemplate->itemTemplateName.c_str())->name;
        }

        observable = true;
    }

    CollectableEntity::~CollectableEntity() {

    }


    void CollectableEntity::Update() {        
        SceneryEntity::Update();
    }

    void CollectableEntity::SetPosition(Ogre::Vector3 pos) {
        SceneryEntity::SetPosition(pos);
    }

    void CollectableEntity::UpdatePosition() {
        SceneryEntity::UpdatePosition();
    }




    ActionType CollectableEntity::GetDefaultActionType() {
    	return AT_PICK;
    }

}
