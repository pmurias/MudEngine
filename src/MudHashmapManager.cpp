#include <MudHashmapManager.h>

namespace Mud {

    template<class T>
    T HashmapManager<T>::getElement(const char *key) {        
        return map[key];
    }

}

