#ifndef _MudLuaWrappers
#define _MudLuaWrappers

#include <lua.hpp>

namespace Mud {

	namespace LuaWrappers {
		static int VisibleEntity_getDisplayName(lua_State *);

		void RegisterAll();
	}
}

#endif

