#ifndef _MudCharacterPickedCollectableEvent
#define _MudCharacterPickedCollectableEvent

#include <events/MudEvent.h>

namespace Mud {

	class CharacterEntity;
	class CollectableEntity;

	class CharacterPickedCollectableEvent  : public Event {
	public:
		CollectableEntity *collectable;
		CharacterEntity *character;

		CharacterPickedCollectableEvent(CharacterEntity *_character, CollectableEntity *_collectable);
		~CharacterPickedCollectableEvent();

		void Update();
	};
}

#endif
