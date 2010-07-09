#include <MudLuaIntResult.h>
#include <MudCore.h>

namespace Mud {

	void LuaIntResult::Pop() {
		value = lua_tointeger(Core::GetInstance().lua.machine, -1);
		lua_pop(Core::GetInstance().lua.machine, 1);
	}

}
