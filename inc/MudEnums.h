#ifndef _MudEnums
#define _MudEnums

namespace Mud {

    /** Entity template, and entity types
     */
    enum EntityTemplateType {
        ETT_NONE,
        ETT_SCENERY,
        ETT_CONTAINER,
        ETT_COLLECTABLE
    };

    /** Bounding volume types, used by various VisibleEntity
     * objects
     */
    enum BoundingVolumeType {
        BVT_BOX,
        BVT_SPHERE
    };

    /** Character state flags
     */
    enum CharacterState {
        CS_IDLE = 1,
        CS_MOVING_FORWARD = 1 << 1,
        CS_TURNING_LEFT = 1 << 2,        
        CS_TURNING_RIGHT = 1 << 3,
        CS_RUNNING = 1 << 4,
        CS_WALKING = 1 << 5
    };

    /** Item classes
     */
    enum ItemClass {
        IC_GENERAL,
    };

}

#endif
