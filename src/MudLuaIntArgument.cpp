#include <MudLuaIntArgument.h>
#include <MudCore.h>

namespace Mud {

	LuaIntArgument::LuaIntArgument(int v) {
		value = v;
	}

	void LuaIntArgument::Push() {
		lua_pushnumber(Core::GetInstance().lua.machine, value);
	}

}
