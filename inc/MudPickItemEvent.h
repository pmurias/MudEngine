#ifndef _MudPickItemEvent
#define _MudPickItemEvent

#include <MudEvent.h>

namespace Mud {

	class CharacterEntity;
	class Item;

	class PickItemEvent : public Event {
	public:
		Item *item;
		CharacterEntity *character;

		PickItemEvent(CharacterEntity *_character, Item *_item);
		~PickItemEvent();

		void Update();
	};
}

#endif
