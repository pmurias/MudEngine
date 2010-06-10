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
    chr->mass = 70;
    chr->radius = 0.75 * 0.5;
    chr->height = 1.75 * 0.5;
    chr->walkSpeed = 2.0;
    chr->runFactor = 3.0;
    chr->headOffset = Ogre::Vector3(0,1,0);
    core.entityTemplateManager.AddTemplate("char", chr);


    Mud::SceneryEntityTemplate *temp = new Mud::SceneryEntityTemplate();
    temp->meshName = "box.mesh";
    temp->collidable = true;
    temp->dynamic = true;
    temp->mass = 3000;
    temp->boxSize = btVector3(1,1,1);
    temp->boundingVolumeType = Mud::BVT_BOX;
    core.entityTemplateManager.AddTemplate("test", temp);

    temp = new Mud::SceneryEntityTemplate();
    temp->meshName = "box.mesh";
    temp->collidable = true;
    temp->dynamic = false;
    temp->mass = 0;
    temp->boxSize = btVector3(1,1,1);
    temp->boundingVolumeType = Mud::BVT_BOX;
    core.entityTemplateManager.AddTemplate("test2", temp);

    Mud::SceneryEntity *ent = new Mud::SceneryEntity("Box1", "test");
    ent->SetPosition(Ogre::Vector3(3, 1, 0));
    core.entityManager.AddEntity(ent);

    ent = new Mud::SceneryEntity("Box2", "test");
    ent->SetPosition(Ogre::Vector3(4, 3, 1));
    core.entityManager.AddEntity(ent);
    
    ent = new Mud::SceneryEntity("Box3", "test2");
    ent->SetPosition(Ogre::Vector3(-3, 1, 0));
    core.entityManager.AddEntity(ent);


    Mud::CharacterEntity *player = new Mud::CharacterEntity("NPC", "char");
    player->SetPosition(Ogre::Vector3(0,6,6));
    player->state |= Mud::CS_IDLE;
    core.entityManager.AddEntity(player);

    player = new Mud::CharacterEntity("Player", "char");
    player->SetPosition(Ogre::Vector3(6,6,6));
    core.entityManager.AddEntity(player);

    core.characterController.cameraDistance = 4.0;
    core.characterController.cameraReaction = 0.1;
    core.characterController.cameraHeight = 1.2;
    core.characterController.character = player;   
    
    bool run = true;

    core.ogreViewport->setBackgroundColour(Ogre::ColourValue(0.1, 0.0, 0.0));

    while (run) {
        core.CaptureInput();
        if (core.oisKeyboard->isKeyDown(OIS::KC_ESCAPE)) run=false;        
        core.characterController.HandleInput();

        core.RenderOneFrame();        

        core.entityManager.UpdateEntities();

        core.characterController.UpdateCameraPosition();

    }

    core.DestroyBullet();
    core.DestroyOgre();

    return 0;
}

