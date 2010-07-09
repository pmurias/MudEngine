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
        CS_IDLE,
        CS_MOVING_FORWARD,
        CS_PICKING,
        CS_OPENING,
        CS_CLOSING
    };

    enum CharacterTurning {
    	CT_NONE,
    	CT_LEFT,
    	CT_RIGHT
    };

    enum CharacterMoving {
    	CM_WALK,
    	CM_RUN
    };

    enum CharacterPickingPhase {
    	CPP_BEFORE_PICK,
    	CPP_AFTER_PICK
    };

    enum CharacterOpeningPhase {
    	COP_BEFORE_OPEN,
    	COP_AFTER_OPEN
    };

    enum CharacterClosingPhase {
    	CCP_BEFORE_CLOSE,
    	CCP_AFTER_CLOSE
    };

    enum CharacterAnimationState {
    	CAS_IDLE,
    	CAS_RUN_NOTHING,
    	CAS_PICK,
    	CAS_WALK_NOTHING,
    	CAS_OPEN_MIDDLE,
    	CAS_CLOSE_MIDDLE,
    	CAS_COUNT
    };

    /** Item classes
     */
    enum ItemClass {
        IC_GENERAL,
    };

    /** Action types
     */
    enum ActionType {
        AT_DEFAULT,
        AT_PICK,
        AT_TOGGLE_CONTAINER_STATE
    };

    /** Openable entity usage phases
     */
    enum OpenableContainerState {
    	OCS_IDLE,
    	OCS_OPENING,
    	OCS_CLOSING
    };

}

#endif
