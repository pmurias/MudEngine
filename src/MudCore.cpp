#include <MudCore.h>
#include <MudException.h>

namespace Mud {

    Core &Core::GetInstance() {
        static Core instance;
        return instance;
    }

    void Core::InitOgre() {
        ogreRoot = new Ogre::Root();

        Ogre::ConfigFile cf;
        cf.load("resources.cfg");

        Ogre::ConfigFile::SectionIterator seci = cf.getSectionIterator();
        Ogre::String secName, typeName, archName;
        while (seci.hasMoreElements()) {
            secName = seci.peekNextKey();
            Ogre::ConfigFile::SettingsMultiMap *settings = seci.getNext();
            Ogre::ConfigFile::SettingsMultiMap::iterator i;
            for (i = settings->begin(); i != settings->end(); ++i) {
                typeName = i->first;
                archName = i->second;
                Ogre::ResourceGroupManager::getSingleton().addResourceLocation(
                    archName, typeName, secName);
            }
        }

        if (!ogreRoot->restoreConfig()) {
            if(!ogreRoot->showConfigDialog()) {
                delete ogreRoot;
                throw new Exception("MUD EXCEPTION: Failed creating Ogre root.");
            }
        }

        ogreWindow = ogreRoot->initialise(true);

        Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();

        ogreSceneMgr = ogreRoot->createSceneManager(Ogre::ST_GENERIC);
        ogreCamera = ogreSceneMgr->createCamera("MainCamera");
        ogreCamera->setNearClipDistance(0.1);
        ogreCamera->setFarClipDistance(1000.0);
        ogreCamera->setAspectRatio((float)(ogreWindow->getWidth())/(float)(ogreWindow->getHeight()));
        ogreCamera->setFOVy(Ogre::Degree(60.0f));
        ogreViewport = ogreWindow->addViewport(ogreCamera);

        OIS::ParamList pl;
        size_t windowHnd = 0;
        std::ostringstream windowHndStr;

        ogreWindow->getCustomAttribute("WINDOW", &windowHnd);
        windowHndStr << windowHnd;
        pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

        oisInputMgr = OIS::InputManager::createInputSystem(pl);
        oisKeyboard = static_cast<OIS::Keyboard*>(oisInputMgr->createInputObject(OIS::OISKeyboard, true));
        oisMouse = static_cast<OIS::Mouse*>(oisInputMgr->createInputObject(OIS::OISMouse, true));

        unsigned int width, height, depth;
        int top, left;
        ogreWindow->getMetrics(width, height, depth, left, top);
        const OIS::MouseState &ms = oisMouse->getMouseState(); ms.width = width; ms.height = height;
    }

    void Core::DestroyOgre() {
        oisInputMgr->destroyInputObject(oisMouse);
        oisInputMgr->destroyInputObject(oisKeyboard);
        OIS::InputManager::destroyInputSystem(oisInputMgr); 

        delete ogreRoot;
    }

    void Core::InitBullet() {
        bulBroadphase = new btDbvtBroadphase();
        bulCollisionConfiguration = new btDefaultCollisionConfiguration();
        bulCollisionDispatcher = new btCollisionDispatcher(bulCollisionConfiguration);
        bulPhysicsSolver = new btSequentialImpulseConstraintSolver();

        bulWorld = new btDiscreteDynamicsWorld(
            bulCollisionDispatcher, 
            bulBroadphase, 
            bulPhysicsSolver, 
            bulCollisionConfiguration
            );
        bulWorld->setGravity(btVector3(0, -25, 0));
    }

    void Core::DestroyBullet() {
        delete bulWorld;
        delete bulPhysicsSolver;
        delete bulCollisionDispatcher;
        delete bulCollisionConfiguration;
        delete bulBroadphase;            
    }

    void Core::CaptureInput() {
        oisKeyboard->capture();
        oisMouse->capture();
    }

    void Core::RenderOneFrame() {
        ogreRoot->renderOneFrame();
        bulWorld->stepSimulation(1.0/60.0);

        ogreWindow->update();
    }
}

