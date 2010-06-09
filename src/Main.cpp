#include <MudCore.h>
#include <MudSceneryEntityTemplate.h>
#include <MudCharacterEntityTemplate.h>
#include <MudSceneryEntity.h>
#include <MudCharacterEntity.h>
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

    core.ogreSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_MODULATIVE);

    Mud::CharacterEntityTemplate *chr = new Mud::CharacterEntityTemplate();
    chr->meshName="capsule.mesh";
    chr->mass = 10;
    chr->radius = 0.75 * 0.5;
    chr->height = 1.2;
    chr->headOffset = Ogre::Vector3(0,1,0);
    core.entityTemplateManager.addTemplate("char", chr);


    Mud::SceneryEntityTemplate *temp = new Mud::SceneryEntityTemplate();
    temp->meshName = "box.mesh";
    temp->collidable = true;
    temp->dynamic = true;
    temp->mass = 900;
    temp->boxSize = btVector3(1,1,1);
    temp->boundingVolumeType = Mud::BVT_BOX;
    core.entityTemplateManager.addTemplate("test", temp);

    temp = new Mud::SceneryEntityTemplate();
    temp->meshName = "box.mesh";
    temp->collidable = true;
    temp->dynamic = false;
    temp->mass = 0;
    temp->boxSize = btVector3(1,1,1);
    temp->boundingVolumeType = Mud::BVT_BOX;
    core.entityTemplateManager.addTemplate("test2", temp);

    Mud::SceneryEntity *ent = new Mud::SceneryEntity();
    ent->Create("Box", "test");
    ent->SetPosition(Ogre::Vector3(3, 1, 0));

    Mud::SceneryEntity *ent2 = new Mud::SceneryEntity();
    ent2->Create("Box2", "test2"); 
    ent2->SetPosition(Ogre::Vector3(-3, 1, 0));

    Mud::CharacterEntity *player = new Mud::CharacterEntity();
    player->Create("Player", "char");
    player->SetPosition(Ogre::Vector3(6,6,6));

    core.characterController.cameraDistance = 6.0;
    core.characterController.cameraReaction = 0.1;
    core.characterController.cameraHeight = 2.0;
    core.characterController.character = player;    
    
    bool run = true;

    core.ogreViewport->setBackgroundColour(Ogre::ColourValue(0.1, 0.0, 0.0));

    while (run) {
        core.CaptureInput();
        if (core.oisKeyboard->isKeyDown(OIS::KC_ESCAPE)) run=false;        
        if (core.oisKeyboard->isKeyDown(OIS::KC_W)) {
            player->body->setLinearVelocity(btVector3(0, 0, 6));
        } else
        if (core.oisKeyboard->isKeyDown(OIS::KC_S)) {
            player->body->setLinearVelocity(btVector3(0, 0, -6));
        } else
        if (core.oisKeyboard->isKeyDown(OIS::KC_A)) {
            player->body->setLinearVelocity(btVector3(6, 0, 0));
        } else
        if (core.oisKeyboard->isKeyDown(OIS::KC_D)) {
            player->body->setLinearVelocity(btVector3(-6, 0, 0));
        } else {
            player->body->setLinearVelocity(btVector3(0, player->body->getLinearVelocity().y(), 0));
        }

        core.RenderOneFrame();        

        player->UpdatePosition();
        ent->UpdatePosition();
        ent2->UpdatePosition();

        core.characterController.UpdateCameraPosition();

    }

    core.DestroyBullet();
    core.DestroyOgre();

    return 0;
}

