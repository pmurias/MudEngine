#ifndef _MudEntity
#define _MudEntity

#include <string>

namespace Mud {

    class Entity {
    public:
        std::string name;

        virtual void Create(const char *name, const char *entityTemplateName);        
        virtual void Destroy();
    };

}

#endif

