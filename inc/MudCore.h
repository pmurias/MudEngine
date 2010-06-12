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
#include <MudUtils.h>

namespace Mud {

    /** Main class, singleton
     */
    class Core {
    public:
           
        Ogre::Root *ogreRoot;
        Ogre::RenderWindow* ogreWindow;
        Ogre::SceneManager* ogreSceneMgr;
        Ogre::Camera* ogreCamera;
        Ogre::Viewport* ogreViewport;
        OIS::Keyboard* oisKeyboard;
        OIS::Mouse* oisMouse;
        OIS::InputManager *oisInputMgr;

        btBroadphaseInterface *bulBroadphase;
        btDefaultCollisionConfiguration *bulCollisionConfiguration;
        btCollisionDispatcher *bulCollisionDispatcher;
        btSequentialImpulseConstraintSolver *bulPhysicsSolver;
        btDiscreteDynamicsWorld *bulWorld;    

        float timeDelta;
        float timeStep;

        World world;
        EntityManager entityManager;
        EntityTemplateManager entityTemplateManager;
        TextBoxManager textBoxManager;
        Console console;
        
        CharacterController characterController;

        static Core &GetInstance();

        /// Initialises Ogre3d engine
        void InitOgre();
        void InitBullet();

        void DestroyOgre();
        void DestroyBullet();

        /// Grabs input from OIS devices
        void CaptureInput();
        /// Updates physical simulation and renders frame using Ogre
        void RenderOneFrame();
    };
}

#endif

