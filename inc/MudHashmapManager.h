#ifndef _MudHashmapManager
#define _MudHashmapManager

#include <tr1/unordered_map>
#include <string>

#include <MudException.h>

namespace Mud {
 
    /** Generic hashmap based manager
     */
    template <class T>
    class HashmapManager {
    public:        
        typedef std::tr1::unordered_map<std::string, T> Hashmap;
        Hashmap map;
        std::string managerName;

        /// Gets key value without checking if it exists
        T GetElement(const char *key) {        
            return map[key];
        }

        /// Get key value or throws exception if it doesn't exists
        T GetSafeElement(const char *key) {
            typename Hashmap::iterator findResult =
                map.find(key);
            if (findResult == map.end()) {
                throw new Exception("%s has not found key \"%s\".", managerName.c_str(), key);
            } else {
                return findResult->second;
            }
        }

        /// Returns true if map contains key value
        bool FindElement(const char *key) {
            return (map.find(key) != map.end());
        }

        /// Sets key value without checking if it already exists
        void AddElement(const char *key, T elem) {
            map[key] = elem;
        }

        /// Sets key value or throws exception if it already exists
        void AddSafeElement(const char *key, T elem) {
            if (FindElement(key)) {
                throw new Exception("%s already has key \"%s\".", managerName.c_str(), key);
            } else {
                map[key]=elem;
            }
        }

        /// Removes key value
        void RemoveElement(const char *key) {
        	map.erase(key);
        }

    };

}

#endif

