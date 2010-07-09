#include <MudCore.h>
#include <MudLuaWrappers.h>

Mud::Core &core = Mud::Core::GetInstance();

int main(void) {
    core.InitOgre();
    core.InitBullet();
    core.lua.Init();
    Mud::LuaWrappers::RegisterAll();

    core.lua.LoadScript("script.lua");

    Mud::LuaFunction *fun = core.lua.CreateFunction("test", 1, 1);
    fun->SetArgument(0, new Mud::LuaIntArgument(666));
    fun->SetResult(0, new Mud::LuaIntResult());

    fun->Call();

    printf("Call Value: %d\n", dynamic_cast<Mud::LuaIntResult* >(fun->GetResult(0))->value);

    core.textBoxManager.Init();
    core.console.CreateLines(20, "BlueHigh", "16", Ogre::ColourValue(1.0, 0.0, 0.0));

    core.world.SetupWorldGraphics("testLevel.mesh");
    core.world.SetupWorldPhysics("testLevel.mesh");
    core.ogreCamera->setPosition(Ogre::Vector3(-15,20,-15));
    core.ogreCamera->lookAt(Ogre::Vector3(0,0,0));


    Ogre::Light *light = core.ogreSceneMgr->createLight("Sun");
    light->setType(Ogre::Light::LT_POINT);
    light->setDirection(Ogre::Vector3(0.5,-1,1));
    light->setPosition(0, 20, 0);
    light->setAttenuation(100, 1.0, 0.02, 0.001);
    light->setCastShadows(true);

    light = core.ogreSceneMgr->createLight("Sun2");
    light->setType(Ogre::Light::LT_DIRECTIONAL);
    light->setDiffuseColour(Ogre::ColourValue(0.2, 0.3, 0.3));
    light->setDirection(Ogre::Vector3(-1.0,-1,-0.7));

    core.ogreSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);
    core.ogreSceneMgr->setAmbientLight(Ogre::ColourValue(0,0,0));



 //-- ----------- ITEM TEMPLATES ---------------------
    Mud::ItemTemplate *itTemp = new Mud::ItemTemplate();
    itTemp->description ="Descripton.";
    itTemp->name = "Med Kit";
    itTemp->value = 666;
    itTemp->weight = 10;
    itTemp->itemClass = Mud::IC_GENERAL;
    core.itemFactory.AddItemTemplate("medkit", itTemp);

    itTemp = new Mud::ItemTemplate();
        itTemp->description ="Pilka w grze";
        itTemp->name = "Fotbul";
        itTemp->value = 666;
        itTemp->weight = 10;
        itTemp->itemClass = Mud::IC_GENERAL;
        core.itemFactory.AddItemTemplate("ball", itTemp);

 // ---------------------- CHARACTER TEMPLATES --------------
    Mud::CharacterEntityTemplate *chr = new Mud::CharacterEntityTemplate();
    chr->meshName="Man.mesh";
    chr->displayName = "Capsule";
    chr->observable = true;
    chr->mass = 2;
    chr->radius = 0.45 * 0.5;
    chr->height = 2.8 * 0.5;
    chr->walkSpeed = 1.1;
    chr->runFactor = 4.0;
    chr->headOffset = Ogre::Vector3(0,0.7,0);
    core.entityTemplateManager.AddTemplate("char", chr);

  /// --------------------------SCENERY TEMPLATES --------------------
    Mud::SceneryEntityTemplate *temp = new Mud::SceneryEntityTemplate();
    temp->meshName = "box.mesh";
    temp->displayName = "Crate";
    temp->observable = true;
    temp->collidable = true;
    temp->dynamic = true;
    temp->mass = 300;
    temp->boxSize = btVector3(1,1,1);
    temp->boundingVolumeType = Mud::BVT_BOX;
    core.entityTemplateManager.AddTemplate("test", temp);

    temp = new Mud::SceneryEntityTemplate();
    temp->meshName = "box.mesh";
    temp->displayName = "Heavy Box";
    temp->observable = true;
    temp->collidable = true;
    temp->dynamic = false;
    temp->mass = 0;
    temp->boxSize = btVector3(1,1,1);
    temp->boundingVolumeType = Mud::BVT_BOX;
    core.entityTemplateManager.AddTemplate("test2", temp);

 //=---------------------------------- CONTAINER TEMPLATES --------------------------
    Mud::ContainerEntityTemplate *contT = new Mud::ContainerEntityTemplate();
    contT->meshName = "bookshelf.mesh";
    contT->displayName = "Bookshelf";
    contT->collidable = true;
    contT->dynamic = true;
    contT->mass = 30;
    contT->boxSize = btVector3(0.7, 1.2, 0.3);
    contT->boundingVolumeType = Mud::BVT_BOX;
    core.entityTemplateManager.AddTemplate("bookshelf", contT);

    contT = new Mud::ContainerEntityTemplate();
	contT->meshName = "chest.mesh";
	contT->displayName = "Chest";
	contT->collidable = true;
	contT->dynamic = true;
	contT->mass = 30;
	contT->boxSize = btVector3(0.6, 0.3, 0.3);
	contT->boundingVolumeType = Mud::BVT_BOX;
	core.entityTemplateManager.AddTemplate("chest", contT);

	contT = new Mud::ContainerEntityTemplate();
		contT->meshName = "Locker.mesh";
		contT->displayName = "Locker";
		contT->collidable = true;
		contT->dynamic = true;
		contT->mass = 90;
		contT->boxSize = btVector3(0.3, 1.1, 0.4);
		contT->boundingVolumeType = Mud::BVT_BOX;
		core.entityTemplateManager.AddTemplate("locker", contT);

 // --------------------------------- COLLECTABLE TEMPLATES --------------------------
    Mud::CollectableEntityTemplate *colT = new Mud::CollectableEntityTemplate();
    colT->meshName = "medkit.mesh";
    colT->mass = 1.0;
    colT->itemTemplateName = "medkit";
    colT->boxSize = btVector3(0.11, 0.11, 0.11);
    colT->boundingVolumeType = Mud::BVT_BOX;
    core.entityTemplateManager.AddTemplate("medkit", colT);

    colT = new Mud::CollectableEntityTemplate();
	colT->meshName = "Ball.mesh";
	colT->itemTemplateName = "ball";
	colT->radius = 0.105f;
	colT->boundingVolumeType = Mud::BVT_SPHERE;
	colT->mass = 0.05;
	core.entityTemplateManager.AddTemplate("ball", colT);


    Mud::SceneryEntity *ent = new Mud::SceneryEntity("Box1", "test2");
    ent->SetPosition(Ogre::Vector3(3, 1, 0));
    core.entityManager.AddEntity(ent);

    ent = new Mud::SceneryEntity("Box2", "test");
    ent->SetPosition(Ogre::Vector3(4, 3, 1));
    core.entityManager.AddEntity(ent);
    
    ent = new Mud::SceneryEntity("Box3", "test");
    ent->SetPosition(Ogre::Vector3(-3, 1, 0));
    core.entityManager.AddEntity(ent);

    Mud::ContainerEntity *bookshelf = new Mud::ContainerEntity("Bookshelf1", "bookshelf");
    bookshelf->SetPosition(Ogre::Vector3(4, 1.2, -5));
    core.entityManager.AddEntity(bookshelf);

    Mud::OpenableContainerEntity *chest = new Mud::OpenableContainerEntity("Chest1", "chest");
    chest->SetPosition(Ogre::Vector3(2, 1.2, -5));
    core.entityManager.AddEntity(chest);

    Mud::OpenableContainerEntity *locker = new Mud::OpenableContainerEntity("Locker1", "locker");
        locker->SetPosition(Ogre::Vector3(0, 2.2, -12));
        core.entityManager.AddEntity(locker);

        locker = new Mud::OpenableContainerEntity("Locker2", "locker");
                locker->SetPosition(Ogre::Vector3(0.6, 2.2, -12));
                core.entityManager.AddEntity(locker);

    for (int i = 0; i < 10; i++) {
    	char _name[255];
    	sprintf(_name, "Medkit%d", i);
    	Mud::CollectableEntity *medkit = new Mud::CollectableEntity(_name, "medkit");
    	medkit->SetPosition(Ogre::Vector3(4- i*0.3, 1.2, -3.5));
    	core.entityManager.AddEntity(medkit);
    }

    Mud::CollectableEntity *ball = new Mud::CollectableEntity("PilkaWGrze", "ball");
    ball->SetPosition(Ogre::Vector3(-4, 1.2, 3.5));
        	core.entityManager.AddEntity(ball);
        	ball->body->setRestitution(1.0);
        	ball->body->setFriction(0.4);
        	ball->body->setDamping(0.1, 0.2);

    Mud::RegionEntity *region0 = new Mud::RegionEntity("Region0", "Region0.mesh");
    region0->callback = core.lua.GetFunction("region0_onEnter", 1, 0);
    core.entityManager.AddEntity(region0);


    Mud::CharacterEntity *player = new Mud::CharacterEntity("NPC", "char");
    player->SetPosition(Ogre::Vector3(0,3,6));
    player->generalState = Mud::CS_IDLE;
    core.entityManager.AddEntity(player);

    player = new Mud::CharacterEntity("Player", "char");
    player->SetPosition(Ogre::Vector3(6,3,6));
    core.entityManager.AddEntity(player);

    core.characterController.cameraDistance = 4.0;
    core.characterController.cameraReaction = 0.06;
    core.characterController.cameraHeight = 1.2;
    core.characterController.character = player;   
    
    bool run = true;

    core.ogreViewport->setBackgroundColour(Ogre::ColourValue(0.1, 0.0, 0.0));

    Mud::TextBox *tbFps = core.textBoxManager.CreateTextBox("tbFps", 750, 10, 100, 30, "BlueHigh", "16", Ogre::ColourValue(0.0, 1.0, 1.0));

    Mud::Entity *lastFocused;

    while (run) {
        core.CaptureInput();
        if (core.oisKeyboard->isKeyDown(OIS::KC_ESCAPE)) run=false;        
        core.characterController.HandleInput();
        core.characterController.HandleFocus();

        tbFps->SetFormattedCaption("FPS:%d", (int)(core.ogreWindow->getAverageFPS()));
        core.RenderOneFrame();

        if (lastFocused != core.characterController.focusedEntity) {
        	lastFocused = core.characterController.focusedEntity;
        	if (lastFocused) {
        		// core.console.Print("Looking at %s", core.characterController.focusedEntity->displayName.c_str());
        	}
        }

        core.eventManager.UpdateEvents();
        core.entityManager.UpdateEntities();

        core.characterController.UpdateCameraPosition();

    }

    core.DestroyBullet();
    core.DestroyOgre();

    return 0;
}

