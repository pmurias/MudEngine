#include <MudLua.h>
#include <MudLuaFunction.h>

namespace Mud {

	void Lua::Init() {
		machine = lua_open();

		luaL_openlibs(machine);
	}

	void Lua::Destroy() {
		lua_close(machine);
	}

	void Lua::LoadScript(const char* fileName) {
		luaL_dofile(machine, fileName);
	}

	LuaFunction *Lua::CreateFunction(const char *name, int in, int out) {
		LuaFunction *fun = new LuaFunction(name, in, out);
		AddSafeElement(name, fun);
		return fun;
	}

	LuaFunction *Lua::GetFunction(const char *name) {
		return GetSafeElement(name);
	}

	LuaFunction *Lua::GetFunction(const char *name, int in, int out) {
		if (FindElement(name)) {
			return GetElement(name);
		} else {
			LuaFunction *fun = new LuaFunction(name, in, out);
			AddSafeElement(name, fun);
			return fun;
		}
	}
}
