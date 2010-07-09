#include <MudLuaStringArgument.h>
#include <MudCore.h>

namespace Mud {

	LuaStringArgument::LuaStringArgument(const char *v) {
		value = v;
	}

	void LuaStringArgument::Push() {
		lua_pushstring(Core::GetInstance().lua.machine, value.c_str());
	}

}
