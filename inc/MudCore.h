#ifndef _MudCore_
#define _MudCore_

#include <OGRE/Ogre.h>
#include <OIS/OIS.h>
#include <btBulletDynamicsCommon.h>

#include <MudWorld.h>

namespace Mud {

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

        static Core &GetInstance();

        void InitOgre();
        void InitBullet();

        void DestroyOgre();
        void DestroyBullet();

        void CaptureInput();
        void RenderOneFrame();
    };
}

#endif
