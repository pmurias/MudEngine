#include <events/MudCharacterEnteredRegionEvent.h>
#include <MudRegionEntity.h>
#include <MudCharacterEntity.h>
#include <MudLua.h>
#include <MudCore.h>

namespace Mud {

	CharacterEnteredRegionEvent::CharacterEnteredRegionEvent(CharacterEntity *_character, RegionEntity *_region)
		: Event() {
		character = _character;
		region = _region;
	}

	CharacterEnteredRegionEvent::~CharacterEnteredRegionEvent() {
	}

	void CharacterEnteredRegionEvent::Update() {
		if (region->callback != NULL) {
			region->callback->SetArgument(0, new LuaPtrArgument(character));
			region->callback->Call();
		}
		Finish();
	}

}
