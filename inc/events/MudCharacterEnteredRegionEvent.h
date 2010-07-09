#ifndef _MudCharacterEnteredRegionEvent
#define _MudCharacterEnteredRegionEvent

#include <events/MudEvent.h>

namespace Mud {

	class CharacterEntity;
	class RegionEntity;

	class CharacterEnteredRegionEvent : public Event {
	public:
		RegionEntity *region;
		CharacterEntity *character;

		CharacterEnteredRegionEvent(CharacterEntity *_character, RegionEntity *_region);
		~CharacterEnteredRegionEvent();

		void Update();
	};
}

#endif

