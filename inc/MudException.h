#ifndef _MudException
#define _MudException

#include <string>
#include <cstdio>
#include <cstdarg>

namespace Mud {

    /**
     * Class representing MudEngine exception
     * @remarks
     *  Formatted text exception
     */
    class Exception {
    public:
        /// Exception message string
        std::string message;

        /** Formatted exception text constructor 
         * @param fmt Regular format string
         * */
        Exception(const char *fmt, ...);
    };
}

#endif



