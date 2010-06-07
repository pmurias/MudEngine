#include <MudCore.h>

Mud::Core &core = Mud::Core::GetInstance();

int main(void) {
    core.InitOgre();
    core.InitBullet();

    core.world.SetupWorldGraphics("testLevel.mesh");
    core.world.SetupWorldPhysics("testLevel.mesh");
    core.ogreCamera->setPosition(Ogre::Vector3(0,3,0));
    core.ogreCamera->lookAt(Ogre::Vector3(10,0,10));


    Ogre::Light *light = core.ogreSceneMgr->createLight("Sun");
    light->setType(Ogre::Light::LT_DIRECTIONAL);
    light->setDirection(Ogre::Vector3(0.5,-1,1));

    bool run = true;

    core.ogreViewport->setBackgroundColour(Ogre::ColourValue(0.1, 0.0, 0.0));

    while (run) {
        core.CaptureInput();
        if (core.oisKeyboard->isKeyDown(OIS::KC_ESCAPE)) run=false;

        core.RenderOneFrame();
    }

    core.DestroyBullet();
    core.DestroyOgre();

    return 0;
}

