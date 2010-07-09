#include <events/MudCharacterReceivedItemEvent.h>
#include <MudItem.h>
#include <MudCharacterEntity.h>
#include <MudCore.h>

namespace Mud {

	CharacterReceivedItemEvent::CharacterReceivedItemEvent(CharacterEntity *_character, Item *_item)
		: Event() {
		character = _character;
		item = _item;
	}

	CharacterReceivedItemEvent::~CharacterReceivedItemEvent() {
	}

	void CharacterReceivedItemEvent::Update() {
		character->Pick(item);
		Finish();
	}

}
