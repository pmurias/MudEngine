#ifndef _MudLua
#define _MudLua

#include <MudHashmapManager.h>
#include <MudLuaFunction.h>
#include <MudLuaArgument.h>
#include <MudLuaIntArgument.h>
#include <MudLuaPtrArgument.h>
#include <MudLuaResult.h>
#include <MudLuaIntResult.h>

#include <lua.hpp>

namespace Mud {

	class LuaFunction;

	/**
	 * Contains everything lua-related
	 */
	class Lua : public HashmapManager<LuaFunction*> {
	public:
		lua_State *machine;

		/// Inits LUA state and libs
		void Init();
		/// Destroys LUA machine
		void Destroy();

		void LoadScript(const char *fileName);

		LuaFunction *CreateFunction(const char *name, int in, int out);

		LuaFunction *GetFunction(const char *name);

		LuaFunction *GetFunction(const char *name, int in, int out);
	};

}

#endif
