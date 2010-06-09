#include <MudCore.h>
#include <MudSceneryEntityTemplate.h>
#include <MudSceneryEntity.h>
#include <MudUtils.h>

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

    Mud::SceneryEntityTemplate *temp = new Mud::SceneryEntityTemplate();
    temp->meshName = "box.mesh";
    temp->collidable = true;
    temp->dynamic = true;
    temp->mass = 3;
    temp->boxSize = btVector3(1,1,1);
    temp->boundingVolumeType = Mud::BVT_BOX;
    core.entityTemplateManager.map["test"] = temp;

    temp = new Mud::SceneryEntityTemplate();
    temp->meshName = "box.mesh";
    temp->collidable = true;
    temp->dynamic = false;
    temp->mass = 0;
    temp->boxSize = btVector3(1,1,1);
    temp->boundingVolumeType = Mud::BVT_BOX;
    core.entityTemplateManager.map["test2"] = temp;

    Mud::SceneryEntity *ent = new Mud::SceneryEntity();
    ent->Create("Box", "test");
    ent->SetPosition(Ogre::Vector3(3, 1, 0));
    ent->body->setDamping(0.9, 0.9);

    Mud::SceneryEntity *ent2 = new Mud::SceneryEntity();
    ent2->Create("Box2", "test2");
    ent2->SetPosition(Ogre::Vector3(-3, 1, 0));
    ent2->body->setDamping(0.9, 0.9);

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

        ent->UpdatePosition();
        ent2->UpdatePosition();

    }

    core.DestroyBullet();
    core.DestroyOgre();

    return 0;
}

