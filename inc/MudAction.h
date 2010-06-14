#ifndef _MudAction
#define _MudAction

#include <MudEnums.h>

namespace Mud {

	class CharacterEntity;

	/**
	 * Action performed by character on various entities
	 */
    class Action {
    public:
        ActionType type;

        /// Character performing this action
        CharacterEntity *performer;

        Action(ActionType t, CharacterEntity *perf);
    };

}

#endif

