#ifndef _MudCharacterReceivedItemEvent
#define _MudCharacterReceivedItemEvent

#include <events/MudEvent.h>

namespace Mud {

	class CharacterEntity;
	class Item;

	class CharacterReceivedItemEvent : public Event {
	public:
		Item *item;
		CharacterEntity *character;

		CharacterReceivedItemEvent(CharacterEntity *_character, Item *_item);
		~CharacterReceivedItemEvent();

		void Update();
	};
}

#endif
