#ifndef _MudEnums
#define _MudEnums

namespace Mud {

    enum EntityTemplateType {
        ETT_NONE,
        ETT_SCENERY,
        ETT_CONTAINER,
        ETT_COLLECTABLE
    };

    enum BoundingVolumeType {
        BVT_BOX,
        BVT_SPHERE
    };

    enum CharacterState {
        CS_IDLE = 1,
        CS_MOVING_FORWARD = 1 << 1,
        CS_TURNING_LEFT = 1 << 2,        
        CS_TURNING_RIGHT = 1 << 3,
        CS_RUNNING = 1 << 4,
        CS_WALKING = 1 << 5
    };

    enum ItemClass {
        IC_GENERAL,
    };

}

#endif
