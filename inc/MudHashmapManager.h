#ifndef _MudHashmapManager
#define _MudHashmapManager

#include <tr1/unordered_map>
#include <string>

#include <MudException.h>

namespace Mud {
    
    template <class T>
    class HashmapManager {
    public:        
        typedef std::tr1::unordered_map<std::string, T> Hashmap;
        Hashmap map;
        std::string managerName;

        T GetElement(const char *key) {        
            return map[key];
        }

        T GetSafeElement(const char *key) {
            typename Hashmap::iterator findResult =
                map.find(key);
            if (findResult == map.end()) {
                throw new Exception("%s has not found key \"%s\".", managerName.c_str(), key);
            } else {
                return findResult->second;
            }
        }

        bool FindElement(const char *key) {
            return (map.find(key) != map.end());
        }

        void AddElement(const char *key, T elem) {
            map[key] = elem;
        }

        void AddSafeElement(const char *key, T elem) {
            if (FindElement(key)) {
                throw new Exception("%s already has key \"%s\".", managerName.c_str(), key);
            } else {
                map[key]=elem;
            }
        }

    };

}

#endif

