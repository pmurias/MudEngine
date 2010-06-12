#ifndef _MudEntity
#define _MudEntity

#include <string>

namespace Mud {

    /** General game entity abstract class. 
     */
    class Entity {
    public:
        /// Unique name
        std::string name;
        
        Entity(const char *entName, const char *entityTemplateName);        
        virtual void Destroy();

        virtual void Update();
    };

}

#endif

