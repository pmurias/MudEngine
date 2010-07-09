#ifndef _MudCharacterClosedContainerEvent
#define _MudCharacterClosedContainerEvent

#include <events/MudEvent.h>

namespace Mud {

	class CharacterEntity;
	class OpenableContainerEntity;

	class CharacterClosedContainerEvent : public Event {
	public:
		OpenableContainerEntity *container;
		CharacterEntity *character;

		CharacterClosedContainerEvent(CharacterEntity *_character, OpenableContainerEntity *_container);
		~CharacterClosedContainerEvent();

		void Update();
	};
}

#endif
