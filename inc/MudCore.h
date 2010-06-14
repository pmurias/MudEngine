#ifndef _MudCore_
#define _MudCore_

#include <OGRE/Ogre.h>
#include <OIS/OIS.h>
#include <btBulletDynamicsCommon.h>

#include <MudWorld.h>
#include <MudEntityTemplateManager.h>
#include <MudEntityManager.h>
#include <MudTextBoxManager.h>
#include <MudConsole.h>
#include <MudCharacterController.h>
#include <MudSceneryEntityTemplate.h>
#include <MudCharacterEntityTemplate.h>
#include <MudContainerEntityTemplate.h>
#include <MudCollectableEntityTemplate.h>
#include <MudSceneryEntity.h>
#include <MudCharacterEntity.h>
#include <MudContainerEntity.h>
#include <MudCollectableEntity.h>
#include <MudItem.h>
#include <MudItemTemplate.h>
#include <MudItemFactory.h>
#include <MudInventory.h>
#include <MudUtils.h>

namespace Mud {

    /** Main class, singleton
     */
    class Core {
    public:
 
        /// Ogre renderer Root
        Ogre::Root *ogreRoot;
        /// Ogre render window
        Ogre::RenderWindow* ogreWindow;
        /// Ogre scene manager
        Ogre::SceneManager* ogreSceneMgr;
        /// Main game camera
        Ogre::Camera* ogreCamera;
        /// Ogre viewport
        Ogre::Viewport* ogreViewport;
        /// OIS input device - keyboard
        OIS::Keyboard* oisKeyboard;
        /// OIS input device - mouse
        OIS::Mouse* oisMouse;
        /// OIS input manager
        OIS::InputManager *oisInputMgr;

        /// Bullet engine collision optimizer
        btBroadphaseInterface *bulBroadphase;
        /// Bullet collision configuration
        btDefaultCollisionConfiguration *bulCollisionConfiguration;
        /// Bullet dispatcher
        btCollisionDispatcher *bulCollisionDispatcher;
        /// Bullet simulation solver
        btSequentialImpulseConstraintSolver *bulPhysicsSolver;
        /// Bullet discrete dynamics world
        btDiscreteDynamicsWorld *bulWorld;    

        /// Game engine world
        World world;
        /// Entity manager which creates and manages all entities
        EntityManager entityManager;
        /// Entity template manager which holds all entity templates
        EntityTemplateManager entityTemplateManager;
        /// Factory used to create Item instances and hold ItemTemplate's
        ItemFactory itemFactory;
        /// Manager owning all text boxes
        TextBoxManager textBoxManager;
        /// On-screen console
        Console console;
        
        /// Main character controller
        CharacterController characterController;

        /// Singleton accesor
        static Core &GetInstance();

        /// Initializes Ogre-related objects
        void InitOgre();
        /// Initializes Bullet-related objects
        void InitBullet();

        /// Destroys Ogre-related objects
        void DestroyOgre();
        /// Destroys Bullet-related objects
        void DestroyBullet();

        /// Grabs input from OIS devices
        void CaptureInput();
        /// Updates physical simulation and renders frame using Ogre
        void RenderOneFrame();
    };
}

#endif

