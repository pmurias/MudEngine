#ifndef _MudEntity
#define _MudEntity

#include <string>

namespace Mud {

    class Entity {
    public:
        std::string name;

        Entity(const char *entName, const char *entityTemplateName);        
        virtual void Destroy();

        virtual void Update();
    };

}

#endif

