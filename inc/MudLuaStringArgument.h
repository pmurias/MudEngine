#ifndef _MudLuaStringArgument
#define _MudLuaStringArgument

#include <MudLuaArgument.h>
#include <string>

namespace Mud {

	class LuaStringArgument : public LuaArgument {
	public:
		std::string value;

		LuaStringArgument(const char *v);

		void Push();
	};
}

#endif
