#ifndef _MudHashmapManager
#define _MudHashmapManager

#include <tr1/unordered_map>
#include <string>

#include <MudException.h>

namespace Mud {
    
    template <class T>
    class HashmapManager {
    public:
        std::tr1::unordered_map<std::string, T> map;
        std::string managerName;

        T getElement(const char *key) {        
            return map[key];
        }

        T getSafeElement(const char *key) {
            if (!findElement(key)) {
                throw new Exception("%s has not found key \"%s\".", managerName.c_str(), key);
            }
            else
                return map[key];
        }

        bool findElement(const char *key) {
            return (map.find(key) != map.end());
        }
    };

}

#endif

