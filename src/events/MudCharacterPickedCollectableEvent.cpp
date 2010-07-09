#include <events/MudCharacterPickedCollectableEvent.h>
#include <events/MudCharacterReceivedItemEvent.h>
#include <MudItem.h>
#include <MudCollectableEntity.h>
#include <MudCharacterEntity.h>
#include <MudCore.h>

namespace Mud {

	CharacterPickedCollectableEvent::CharacterPickedCollectableEvent(CharacterEntity *_character, CollectableEntity *_collectable)
		: Event() {
		character = _character;
		collectable = _collectable;
	}

	CharacterPickedCollectableEvent::~CharacterPickedCollectableEvent() {
	}

	void CharacterPickedCollectableEvent::Update() {
		Core::GetInstance().entityManager.QueueToDestroy(collectable);
		Core::GetInstance().eventManager.QueueEvent(new CharacterReceivedItemEvent(character, collectable->item));
		Finish();
	}

}
