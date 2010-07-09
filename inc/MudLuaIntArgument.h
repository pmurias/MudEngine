#ifndef _MudLuaIntArgument
#define _MudLuaIntArgument

#include <MudLuaArgument.h>

namespace Mud {

	class LuaIntArgument : public LuaArgument {
	public:
		int value;

		LuaIntArgument(int v);

		void Push();
	};
}


#endif
