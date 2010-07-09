#ifndef _MudContainerEntity
#define _MudContainerEntity

#include <MudSceneryEntity.h>
#include <MudContainerEntityProperties.h>

namespace Mud {

	class CharacterEntity;

	/**
	 * Various container entity class, used for bookshelves, lockers, etc.
	 */
    class ContainerEntity : public SceneryEntity, public ContainerEntityProperties {
    public:
        ContainerEntity(const char *name, const char *entityTemplateName);
        ~ContainerEntity();

        void Update();

        void SetPosition(Ogre::Vector3 pos);
        void UpdatePosition();

        /// Checks if character can perform access action from it's position
        bool CanCharacterAccessIt(CharacterEntity *character);

        /// For container, default action is plundering
        ActionType GetDefaultActionType();

    };

}

#endif

