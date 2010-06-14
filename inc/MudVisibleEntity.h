#ifndef _MudVisibleEntity
#define _MudVisibleEntity

#include <MudEntity.h>
#include <MudVisibleEntityProperties.h>
#include <MudEnums.h>

#include <OGRE/Ogre.h>
#include <btBulletDynamicsCommon.h>


namespace Mud {

    class Action;

    /** Class representing every entities which have graphical and,
     * optionally physical representation
     */
    class VisibleEntity : public Entity, public VisibleEntityProperties {
    public:    
        Ogre::Entity *entity;
        Ogre::SceneNode *node;

        btRigidBody *body;
        btCollisionShape *collisionShape;

        /** Creates entity using template
         * @param name Unique entity identifier
         * @param entityTemplateName Template name which should be present in EntityTemplateManager
         */
        VisibleEntity(const char *name, const char *entityTemplateName);
        virtual ~VisibleEntity();

        /** Should instantly move entity to specified position
         * @param pos Worldspace position
         */
        virtual void SetPosition(Ogre::Vector3 pos);
        /// Unifies physical body and graphical node position
        virtual void UpdatePosition();

        /// General entity behavior
        virtual void Update();

        /// Used to handle actions when entity is observable
        virtual void ActionPerform(Action *action);

        /// Returns default action type of action performed on this entity
        virtual ActionType GetDefaultActionType();
    };

}

#endif

