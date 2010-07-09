#ifndef _MudOpenableContainerEntity
#define _MudOpenableContainerEntity

#include <MudContainerEntity.h>

namespace Mud {

	/**
	 * Class representing openable container entities - useful for lockers,
	 * wardrobes and other with animable parts.
	 */
	class OpenableContainerEntity : public ContainerEntity {
	public:
		/// True if container is ready for plundering; Determining default action
		bool isOpen;
		/// State of the container
		OpenableContainerState state;
		/// Ogre animation, names "Open" in mesh
		Ogre::AnimationState *openAnimationState;

		OpenableContainerEntity(const char *name, const char *entityTemplateName);
		~OpenableContainerEntity();

		void Update();

		void SetPosition(Ogre::Vector3 pos);
		void UpdatePosition();

		void StartOpening();
		void StartClosing();
		void ToggleState();
		bool CanCharacterAccessIt(CharacterEntity *character);



		ActionType GetDefaultActionType();

	};
}

#endif
