#include <MudCore.h>

Mud::Core &core = Mud::Core::GetInstance();

int main(void) {
    core.InitOgre();
    core.InitBullet();

    core.world.SetupWorldGraphics("testLevel.mesh");
    core.world.SetupWorldPhysics("testLevel.mesh");
    core.ogreCamera->setPosition(Ogre::Vector3(-15,20,-15));
    core.ogreCamera->lookAt(Ogre::Vector3(0,0,0));


    Ogre::Light *light = core.ogreSceneMgr->createLight("Sun");
    light->setType(Ogre::Light::LT_DIRECTIONAL);
    light->setDirection(Ogre::Vector3(0.5,-1,1));


    btCollisionShape *ballShape = new btSphereShape(1);
    btDefaultMotionState *ballMS = new btDefaultMotionState(
        btTransform(btQuaternion(0,0,0,1), btVector3(6,2,6))
        );
    btVector3 ballInertia(0,0,0);
    ballShape->calculateLocalInertia(1, ballInertia);

    btRigidBody::btRigidBodyConstructionInfo ballCI(1, ballMS, ballShape, ballInertia);
    btRigidBody *ballBody = new btRigidBody(ballCI);
    core.bulWorld->addRigidBody(ballBody);
    ballBody->setDamping(0.5, 0.8);
    ballBody->setActivationState(DISABLE_DEACTIVATION);

    ballBody->setAngularFactor(btVector3(0,1,0));

    Ogre::Entity *entity = core.ogreSceneMgr->createEntity("Ball", "character.mesh");
    Ogre::SceneNode *node = core.ogreSceneMgr->getRootSceneNode()->createChildSceneNode();
    node->attachObject(entity);    

    core.ogreSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);


    bool run = true;

    core.ogreViewport->setBackgroundColour(Ogre::ColourValue(0.1, 0.0, 0.0));

    while (run) {
        core.CaptureInput();
        if (core.oisKeyboard->isKeyDown(OIS::KC_ESCAPE)) run=false;        
        if (core.oisKeyboard->isKeyDown(OIS::KC_W)) {
            ballBody->applyImpulse(btVector3(0.7,0,1), btVector3(0,0,0));
        }
        if (core.oisKeyboard->isKeyDown(OIS::KC_S)) {
            ballBody->applyImpulse(btVector3(-0.7,0,-1), btVector3(0,0,0));
        }

        core.RenderOneFrame();        

        btTransform trans;
        ballBody->getMotionState()->getWorldTransform(trans);
        node->setPosition(Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY(), trans.getOrigin().getZ()));
        node->setOrientation(Ogre::Quaternion(trans.getRotation().getW(), trans.getRotation().getX(), trans.getRotation().getY(), trans.getRotation().getZ()));
    }

    core.DestroyBullet();
    core.DestroyOgre();

    return 0;
}

