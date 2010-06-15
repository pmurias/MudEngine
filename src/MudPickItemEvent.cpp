#include <MudPickItemEvent.h>
#include <MudItem.h>
#include <MudCharacterEntity.h>
#include <MudCore.h>

namespace Mud {

	PickItemEvent::PickItemEvent(CharacterEntity *_character, Item *_item)
		: Event() {
		character = _character;
		item = _item;
	}

	PickItemEvent::~PickItemEvent() {
	}

	void PickItemEvent::Update() {
		character->Pick(item);
		Finish();
	}

}
