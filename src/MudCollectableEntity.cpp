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
        if (entTemplate->item)
            item = entTemplate->item->Clone();

        observable = true;
    }

    void CollectableEntity::Destroy() {
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

}
