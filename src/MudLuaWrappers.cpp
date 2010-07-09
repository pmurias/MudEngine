#include <MudLuaWrappers.h>
#include <MudCore.h>

namespace Mud {
	namespace LuaWrappers {

		int VisibleEntity_getDisplayName(lua_State *L) {
			VisibleEntity *entity = static_cast<VisibleEntity*>(lua_touserdata(L, 1));
			lua_pushstring(L, entity->displayName.c_str());
			return 1;
		}

		void RegisterAll() {
			lua_State *L = Core::GetInstance().lua.machine;

			lua_register(L, "VisibleEntity_getDisplayName", VisibleEntity_getDisplayName);
		}
	}
}
