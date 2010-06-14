#include <MudAction.h>
#include <MudCharacterEntity.h>

namespace Mud {

	Action::Action(ActionType t, CharacterEntity *perf) {
		type = t;
		performer = perf;
	}
}
