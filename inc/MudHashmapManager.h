#ifndef _MudHashmapManager
#define _MudHashmapManager

#include <tr1/unordered_map>
#include <string>

namespace Mud {
    
    template <class T>
    class HashmapManager {
    public:
        std::tr1::unordered_map<std::string, T> map;

        virtual T getElement(const char *key) {
            return map[key];
        }
    };

}

#endif

