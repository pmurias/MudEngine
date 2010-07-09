#include <MudLuaPtrArgument.h>
#include <MudCore.h>

namespace Mud {

	LuaPtrArgument::LuaPtrArgument(void *v) {
		value = v;
	}

	void LuaPtrArgument::Push() {
		lua_pushlightuserdata(Core::GetInstance().lua.machine, value);
	}

}
