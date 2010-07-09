#ifndef _MudLuaIntResult
#define _MudLuaIntResult

#include <MudLuaResult.h>

namespace Mud {

	class LuaIntResult : public LuaResult {
	public:
		int value;

		void Pop();
	};
}


#endif
