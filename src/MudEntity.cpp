#include <MudEntity.h>
#include <cstdio>

namespace Mud {

    Entity::Entity(const char *entName, const char *entityTemplateName) {
        name = entName;
    }

    Entity::~Entity() {
    }

    void Entity::Update() {
    }

}
