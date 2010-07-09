#ifndef _MudLuaPtrArgument
#define _MudLuaPtrArgument

#include <MudLuaArgument.h>

namespace Mud {

	class LuaPtrArgument : public LuaArgument {
	public:
		void *value;

		LuaPtrArgument(void *v);

		void Push();
	};
}

#endif
