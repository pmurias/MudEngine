#ifndef _MudCharacterOpenedContainerEvent
#define _MudCharacterOpenedContainerEvent

#include <events/MudEvent.h>

namespace Mud {

	class CharacterEntity;
	class OpenableContainerEntity;

	class CharacterOpenedContainerEvent : public Event {
	public:
		OpenableContainerEntity *container;
		CharacterEntity *character;

		CharacterOpenedContainerEvent(CharacterEntity *_character, OpenableContainerEntity *_container);
		~CharacterOpenedContainerEvent();

		void Update();
	};
}

#endif
