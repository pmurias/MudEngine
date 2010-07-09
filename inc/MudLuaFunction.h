#ifndef _MudLuaFunction
#define _MudLuaFunction

#include <string>
#include <vector>

namespace Mud {

	class LuaArgument;
	class LuaResult;

	class LuaFunction {
	public:
		std::string name;
		int argCount;
		int resCount;

		std::vector<LuaArgument*> arguments;
		std::vector<LuaResult *> results;

		LuaFunction(const char *fname, int ac, int rc);

		void SetArgument(int i, LuaArgument *arg);
		void SetResult(int i, LuaResult *res);
		LuaResult *GetResult(int i);
		void Call();
	};
}

#endif
