#include <MudException.h>

namespace Mud {

    Exception::Exception(const char *fmt, ...) {
        char out[4096];
        va_list args;
        if (fmt == NULL)
            out[0] = '\0';
        else {
            va_start(args, fmt);
            vsprintf(out, fmt, args);
            va_end(args);
        }
        message = out;
    }
}
