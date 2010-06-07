#ifndef _MudException
#define _MudException

#include <string>
#include <cstdio>
#include <cstdarg>

namespace Mud {

    class Exception {
    public:
        std::string message;

        Exception(const char *fmt, ...);
    };
}

#endif



