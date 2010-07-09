#include <MudLuaFunction.h>
#include <MudLuaArgument.h>
#include <MudLuaResult.h>
#include <MudCore.h>

namespace Mud {

	LuaFunction::LuaFunction(const char *fname, int ac, int rc) {
		name = fname;
		argCount = ac;
		resCount = rc;
		arguments.resize(argCount);
		results.resize(resCount);
	}

	void LuaFunction::SetArgument(int i, LuaArgument *arg) {
		arguments[i] = arg;
	}

	void LuaFunction::SetResult(int i, LuaResult *res) {
		results[i] = res;
	}

	LuaResult *LuaFunction::GetResult(int i) {
		return results[i];
	}

	void LuaFunction::Call() {
		lua_getglobal(Core::GetInstance().lua.machine, name.c_str());
		for (std::vector<LuaArgument*>::iterator it = arguments.begin(); it != arguments.end(); it++) {
			(*it)->Push();
		}
		lua_call(Core::GetInstance().lua.machine, argCount, resCount);
		for (std::vector<LuaResult*>::iterator it = results.begin(); it != results.end(); it++) {
			(*it)->Pop();
		}
	}
}
