#include "TestLevel.h"
#include <glew.h>
#include <SDL.h>
#include <iostream>
#include "Debug.h"
#include "ObjLoader.h"

#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

#include "Pinball.h"
#include "Paddle.h"
#include "Affector.h"
#include "Goal.h"

#include "UIPanel.h"
#include "UIButton.h"
#include "UIImage.h"

TestLevel::TestLevel() {
	camera = new Camera;
	mydesignation = 1;
	menuState = 4;
	lightSource_UI = Vec3(0.0f, 0.0f, 0.0f);
	lightSource_Ambient = Vec3(0.0f, 0.0f, 0.0f);
	Debug::Info("Created Test Level: ", __FILE__, __LINE__);
}

TestLevel::~TestLevel() {}

bool TestLevel::OnCreate() {
	std::string name_ = "";

#pragma region UI Panel Initialization
	Shader* PTR_Shader_Menu = new Shader("shaders/texturePhongVert.glsl", "shaders/texturePhongFrag.glsl");
	if (PTR_Shader_Menu == nullptr) { Debug::FatalError("Couldn't create UI Shader", __FILE__, __LINE__); return false; } // Shader Initialization Check
	if (ObjLoader::loadOBJ("meshes/UI_Mesh.obj") == false) { Debug::FatalError("Couldn't load background object", __FILE__, __LINE__); return false; }
	Mesh* PTR_Mesh_Menu = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);

#pragma region Gameplay UI
	Texture* PTR_Texture_Panel_Gameplay= new Texture();
	if (PTR_Texture_Panel_Gameplay->LoadImage("textures/Menu_Credits.png") == false) { Debug::FatalError("Couldn't load Gameplay UI texture", __FILE__, __LINE__); return false; }

	name_ = "Gameplay_UI";
	TransformComponent* transform_Gameplay = new TransformComponent(Vec3(0.0f, 0.0f, 0.0f), Vec3(7.4f, 4.15f, 1.0f), 0.0f, Matrix4());
	RenderComponent* renderer_Gameplay = new RenderComponent(PTR_Mesh_Menu, PTR_Texture_Panel_Gameplay, PTR_Shader_Menu);

	panel_Gameplay = new UIPanel(name_, false, this, transform_Gameplay, renderer_Gameplay);
	if (panel_Gameplay == nullptr) { Debug::FatalError("Gameplay UI could not be initialized", __FILE__, __LINE__); return false; }
#pragma endregion

#pragma region Begin Play
	Texture* PTR_Texture_Panel_BeginPlay = new Texture();
	if (PTR_Texture_Panel_BeginPlay->LoadImage("textures/Menu_BeginPlay.png") == false) { Debug::FatalError("Couldn't load Begin Play texture", __FILE__, __LINE__); return false; }

	name_ = "Main_Menu";
	TransformComponent* transform_BeginPlay = new TransformComponent(Vec3(0.0f, 0.0f, 0.0f), Vec3(7.4f, 4.15f, 1.0f), 0.0f, Matrix4());
	RenderComponent* renderer_BeginPlay = new RenderComponent(PTR_Mesh_Menu, PTR_Texture_Panel_BeginPlay, PTR_Shader_Menu);

	panel_Menu_BeginPlay = new UIPanel(name_, true, this, transform_BeginPlay, renderer_BeginPlay);
	if (panel_Menu_BeginPlay == nullptr) { Debug::FatalError("Background could not be initialized", __FILE__, __LINE__); return false; }
#pragma endregion

#pragma region Pause Menu
	Texture* PTR_Texture_Panel_Pause = new Texture();
	if (PTR_Texture_Panel_Pause->LoadImage("textures/Menu_Pause.png") == false) { Debug::FatalError("Couldn't load Pause Menu texture", __FILE__, __LINE__); return false; }

	name_ = "Main_Menu";
	TransformComponent* transform_Pause= new TransformComponent(Vec3(0.0f, 0.0f, 0.0f), Vec3(7.4f, 4.15f, 1.0f), 0.0f, Matrix4());
	RenderComponent* renderer_Pause= new RenderComponent(PTR_Mesh_Menu, PTR_Texture_Panel_Pause, PTR_Shader_Menu);

	panel_Menu_Pause= new UIPanel(name_, false, this, transform_Pause, renderer_Pause);
	if (panel_Menu_Pause== nullptr) { Debug::FatalError("Background could not be initialized", __FILE__, __LINE__); return false; }
#pragma endregion

#pragma region Win Menu
	Texture* PTR_Texture_Panel_Win = new Texture();
	if (PTR_Texture_Panel_Win->LoadImage("textures/Menu_Win.png") == false) { Debug::FatalError("Couldn't load Win Menu texture", __FILE__, __LINE__); return false; }

	name_ = "Main_Menu";
	TransformComponent* transform_Win = new TransformComponent(Vec3(0.0f, 0.0f, 0.0f), Vec3(7.4f, 4.15f, 1.0f), 0.0f, Matrix4());
	RenderComponent* renderer_Win = new RenderComponent(PTR_Mesh_Menu, PTR_Texture_Panel_Win, PTR_Shader_Menu);

	panel_Menu_Win = new UIPanel(name_, false, this, transform_Win, renderer_Win);
	if (panel_Menu_Win == nullptr) { Debug::FatalError("Background could not be initialized", __FILE__, __LINE__); return false; }
#pragma endregion

#pragma region Lose Menu
	Texture* PTR_Texture_Panel_Lose = new Texture();
	if (PTR_Texture_Panel_Lose->LoadImage("textures/Menu_Lose.png") == false) { Debug::FatalError("Couldn't load Lose Menu texture", __FILE__, __LINE__); return false; }

	name_ = "Main_Menu";
	TransformComponent* transform_Lose = new TransformComponent(Vec3(0.0f, 0.0f, 0.0f), Vec3(7.4f, 4.15f, 1.0f), 0.0f, Matrix4());
	RenderComponent* renderer_Lose = new RenderComponent(PTR_Mesh_Menu, PTR_Texture_Panel_Lose, PTR_Shader_Menu);

	panel_Menu_Lose = new UIPanel(name_, false, this, transform_Lose, renderer_Lose);
	if (panel_Menu_Lose == nullptr) { Debug::FatalError("Background could not be initialized", __FILE__, __LINE__); return false; }
#pragma endregion

#pragma endregion

#pragma region Buttons
	int arrayLegnth_ = 4;

#pragma region Pause
	Texture* PTR_Texture_Button_Resume = new Texture();
	Texture* PTR_Texture_Button_Replay = new Texture();
	Texture* PTR_Texture_Button_QTM = new Texture();
	Texture* PTR_Texture_Button_QTD = new Texture();
	if (PTR_Texture_Button_Resume->LoadImage("textures/Button_Resume.png") == false) { Debug::FatalError("Couldn't load background texture", __FILE__, __LINE__); return false; }
	if (PTR_Texture_Button_Replay->LoadImage("textures/Button_Replay.png") == false) { Debug::FatalError("Couldn't load background texture", __FILE__, __LINE__); return false; }
	if (PTR_Texture_Button_QTM->LoadImage("textures/Button_QuitToMenu.png") == false) { Debug::FatalError("Couldn't load background texture", __FILE__, __LINE__); return false; }
	if (PTR_Texture_Button_QTD->LoadImage("textures/Button_QuitToDesktop.png") == false) { Debug::FatalError("Couldn't load background texture", __FILE__, __LINE__); return false; }


	arrayLegnth_ = 4;
	std::string names_Pause[4] = { "Resume", "Replay", "QuitToMenu", "QuitToDesktop" };
	// Click Bounds Direction -> Vec4( TopR +x ,  TopR +y ,  BotL -x ,   BotL -y )
	Vec4 clickBounds_Pause[4] = {
		Vec4(710, 279, 568, 201),
		Vec4(711, 400, 568, 319),
		Vec4(818, 519, 461, 440),
		Vec4(853, 640, 425, 559) };
	TransformComponent* transforms_Pause[4] = {
		new TransformComponent(Vec3(0.0f, 0.3f, 1.0f), Vec3(0.1f,0.1f,0.1f), 0.0f, Matrix4()),
		new TransformComponent(Vec3(0.0f, 0.0f, 1.0f), Vec3(0.1f,0.1f,0.1f), 0.0f, Matrix4()),
		new TransformComponent(Vec3(0.0f, -0.3f, 1.0f), Vec3(0.25f,0.1f,0.1f), 0.0f, Matrix4()),
		new TransformComponent(Vec3(0.0f, -0.6f, 1.0f), Vec3(0.3f,0.1f,0.1f), 0.0f, Matrix4()) };
	RenderComponent* renderers_Pause[4] = {
		new RenderComponent(PTR_Mesh_Menu, PTR_Texture_Button_Resume, PTR_Shader_Menu),
		new RenderComponent(PTR_Mesh_Menu, PTR_Texture_Button_Replay, PTR_Shader_Menu),
		new RenderComponent(PTR_Mesh_Menu, PTR_Texture_Button_QTM, PTR_Shader_Menu),
		new RenderComponent(PTR_Mesh_Menu, PTR_Texture_Button_QTD, PTR_Shader_Menu) };

	panel_Menu_Pause->CreateButtons(arrayLegnth_, names_Pause, clickBounds_Pause, transforms_Pause, renderers_Pause);
#pragma endregion

#pragma region Win
	arrayLegnth_ = 3;
	std::string names_Win[3] = { "Replay", "QuitToMenu", "QuitToDesktop" };
	// Click Bounds Direction -> Vec4( TopR +x ,  TopR +y ,  BotL -x ,   BotL -y )
	Vec4 clickBounds_Win[3] = {
		Vec4(710, 279,  568, 201),
		Vec4(818, 399, 461, 320),
		Vec4(852, 520, 425, 439) };
	TransformComponent* transforms_Win[3] = {
		new TransformComponent(Vec3(0.0f, 0.3f, 1.0f), Vec3(0.1f,0.1f,0.1f), 0.0f, Matrix4()),
		new TransformComponent(Vec3(0.0f, 0.0f, 1.0f), Vec3(0.25f,0.1f,0.1f), 0.0f, Matrix4()),
		new TransformComponent(Vec3(0.0f, -0.3f, 1.0f), Vec3(0.3f,0.1f,0.1f), 0.0f, Matrix4()) };
	RenderComponent* renderers_Win[3] = {
		new RenderComponent(PTR_Mesh_Menu, PTR_Texture_Button_Replay, PTR_Shader_Menu),
		new RenderComponent(PTR_Mesh_Menu, PTR_Texture_Button_QTM, PTR_Shader_Menu),
		new RenderComponent(PTR_Mesh_Menu, PTR_Texture_Button_QTD, PTR_Shader_Menu) };

	panel_Menu_Win->CreateButtons(arrayLegnth_, names_Win, clickBounds_Win, transforms_Win, renderers_Win);
#pragma endregion

#pragma region Lose
	arrayLegnth_ = 3;
	std::string names_Lose[3] = { "Replay", "QuitToMenu", "QuitToDesktop" };
	// Click Bounds Direction -> Vec4( TopR +x ,  TopR +y ,  BotL -x ,   BotL -y )
	Vec4 clickBounds_Lose[3] = {
		Vec4(710, 279,  568, 201),
		Vec4(818, 399, 461, 320),
		Vec4(852, 520, 425, 439) };
	TransformComponent* transforms_Lose[3] = {
		new TransformComponent(Vec3(0.0f, 0.3f, 1.0f), Vec3(0.1f,0.1f,0.1f), 0.0f, Matrix4()),
		new TransformComponent(Vec3(0.0f, 0.0f, 1.0f), Vec3(0.25f,0.1f,0.1f), 0.0f, Matrix4()),
		new TransformComponent(Vec3(0.0f, -0.3f, 1.0f), Vec3(0.3f,0.1f,0.1f), 0.0f, Matrix4()) };
	RenderComponent* renderers_Lose[3] = {
		new RenderComponent(PTR_Mesh_Menu, PTR_Texture_Button_Replay, PTR_Shader_Menu),
		new RenderComponent(PTR_Mesh_Menu, PTR_Texture_Button_QTM, PTR_Shader_Menu),
		new RenderComponent(PTR_Mesh_Menu, PTR_Texture_Button_QTD, PTR_Shader_Menu) };

	panel_Menu_Lose->CreateButtons(arrayLegnth_, names_Lose, clickBounds_Lose, transforms_Lose, renderers_Lose);
#pragma endregion

#pragma endregion

#pragma region Health Bar
	Texture* PTR_Texture_Image_Health = new Texture();
	if (PTR_Texture_Image_Health->LoadImage("textures/heart.png") == false) { Debug::FatalError("Couldn't load healthUI texture", __FILE__, __LINE__); return false; }

	const float healthBarOffset = 0.1f;
	float currentOffset = -0.5f;

	std::string names_Image_Health[maxHealth] = {};
	TransformComponent* transforms_Image_Health[maxHealth] = {};
	RenderComponent* renderers_Image_Health[maxHealth] = {};

	for (int i = 0; i < maxHealth; i++) {
		names_Image_Health[i] = ("Health_Icon" + std::to_string(i));
		transforms_Image_Health[i] = new TransformComponent(Vec3(currentOffset, -0.7f, 1.f), Vec3(0.05f, 0.07f, 1.0), 0.0f, Matrix4());
		renderers_Image_Health[i] = new RenderComponent(PTR_Mesh_Menu, PTR_Texture_Image_Health, PTR_Shader_Menu);
		currentOffset += healthBarOffset;
	}
	panel_Gameplay->CreateImages(maxHealth, names_Image_Health, transforms_Image_Health, renderers_Image_Health);
#pragma endregion

#pragma region Time Display
	// Load Health UI Texture
	for (int i = 0; i < 10; i++) {
		PTRs_Textures_Time[i] = new Texture();
		if (PTRs_Textures_Time[i]->LoadImage(("textures/Number_" + std::to_string(i) + ".png").c_str()) == false) { Debug::FatalError("Couldn't load timeUI #" + std::to_string(i) + " texture", __FILE__, __LINE__); return false; }
	}
	
	#pragma region Time Texture Sequence
	int sec = ((int)timeremaining % 60);
	int min = (((int)timeremaining - sec) / 60);
	int x = 0; int y = 0; int z = 0; int w = 0;

	if (min < 10) { y = min; }
	else { x = (min - (min % 10)) / 10; y = (min % 10); }
	if (sec < 10) { w = sec; }
	else { z = (sec - (sec % 10)) / 10; w = (sec % 10); }

	int t[4] = { x,y,z,w };
	#pragma endregion

	// Time UI Initialization
	const float timeBarOffset = 0.1f;
	currentOffset = 4.2f;

	std::string names_Image_Time[4] = {};
	TransformComponent* transforms_Image_Time[4] = {};
	RenderComponent* renderers_Image_Time[4] = {};

	for (int i = 0; i < 4; i++) {
		int j = t[i];
		names_Image_Health[i] = ("Time_Icon" + std::to_string(i));
		transforms_Image_Health[i] = new TransformComponent(Vec3(currentOffset, 0.0f, 1.f), Vec3(0.05f, 0.07f, 1.0), 0.0f, Matrix4());
		renderers_Image_Health[i] = new RenderComponent(PTR_Mesh_Menu, PTR_Texture_Image_Health, PTR_Shader_Menu);
		currentOffset += timeBarOffset;
	}
	//panel_Gameplay->CreateImages(4, names_Image_Time, transforms_Image_Time, renderers_Image_Time);
#pragma endregion

	#pragma region Entities
	
	#pragma region Balls
	//// Load PinBall Mesh
	//if (ObjLoader::loadOBJ("meshes/Menu_Background.obj") == false) { Debug::FatalError("Couldn't load PinBall object", __FILE__, __LINE__); return false; }
	//ball_meshPtr = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);
	//
	//// Load PinBall Texture
	//ball_texturePtr = new Texture();
	//if (ball_texturePtr->LoadImage("textures/Ball.png") == false) { Debug::FatalError("Couldn't load PinBall texture", __FILE__, __LINE__); return false; }


	//// Asset Pointer Check
	//if (ball_meshPtr == nullptr || ball_texturePtr == nullptr) { Debug::FatalError("Couldn't create PinBall assets", __FILE__, __LINE__); return false; }

	//// PinBall Initialization

	//Vec3 randpos[] = {Vec3(0,0,0), Vec3(2,2,0),Vec3(-2,1,0) ,Vec3(3,2,0) ,Vec3(-1,-3,0) };
	//Vec3 randvel[] = {Vec3(0.1,0.5,0), Vec3(0.2,0.1,0),Vec3(0.7,0.3,0) ,Vec3(0.3,0.4,0) ,Vec3(0.1,0.3,0) };

	///*for (int i = 0; i < health; i++) {
	//	balls[i] = new PinBall(ball_meshPtr, UI_shaderPtr, ball_texturePtr, 0.1f, 0.15f);
	//	if (balls[i] == nullptr) {
	//		Debug::FatalError("PinBall [" + std::to_string(i) + "] could not be initialized", __FILE__, __LINE__); return false;
	//	}

	//	balls[i]->setPos(randpos[i]);
	//	balls[i]->setVel(randvel[i]);
	//}*/

	#pragma endregion

	#pragma endregion


#pragma region Garbage Collection
	
#pragma endregion

	return true;
}

void TestLevel::Update(const float deltaTime) {
	switch (menuState) {
	case 0:
		if (!panel_Gameplay->getIsRendered()) { panel_Gameplay->setIsRendered(true); }

		if (panel_Menu_BeginPlay->getIsRendered()) { panel_Menu_BeginPlay->setIsRendered(false); }
		if (panel_Menu_Pause->getIsRendered()) { panel_Menu_Pause->setIsRendered(false); }
		if (panel_Menu_Win->getIsRendered()) { panel_Menu_Win->setIsRendered(false); }
		if (panel_Menu_Lose->getIsRendered()) { panel_Menu_Lose->setIsRendered(false); }
		break;
	case 1:
		if (!panel_Menu_Pause->getIsRendered()) { panel_Menu_Pause->setIsRendered(true); }

		if (panel_Gameplay->getIsRendered()) { panel_Gameplay->setIsRendered(false); }
		if (panel_Menu_BeginPlay->getIsRendered()) { panel_Menu_BeginPlay->setIsRendered(false); }
		if (panel_Menu_Win->getIsRendered()) { panel_Menu_Win->setIsRendered(false); }
		if (panel_Menu_Lose->getIsRendered()) { panel_Menu_Lose->setIsRendered(false); }
		break;
	case 2:
		if (!panel_Menu_Win->getIsRendered()) { panel_Menu_Win->setIsRendered(true); }

		if (panel_Gameplay->getIsRendered()) { panel_Gameplay->setIsRendered(false); }
		if (panel_Menu_BeginPlay->getIsRendered()) { panel_Menu_BeginPlay->setIsRendered(false); }
		if (panel_Menu_Pause->getIsRendered()) { panel_Menu_Pause->setIsRendered(false); }
		if (panel_Menu_Lose->getIsRendered()) { panel_Menu_Lose->setIsRendered(false); }
		break;
	case 3:
		if (!panel_Menu_Lose->getIsRendered()) { panel_Menu_Lose->setIsRendered(true); }

		if (panel_Gameplay->getIsRendered()) { panel_Gameplay->setIsRendered(false); }
		if (panel_Menu_BeginPlay->getIsRendered()) { panel_Menu_BeginPlay->setIsRendered(false); }
		if (panel_Menu_Pause->getIsRendered()) { panel_Menu_Pause->setIsRendered(false); }
		if (panel_Menu_Win->getIsRendered()) { panel_Menu_Win->setIsRendered(false); }
		break;
	case 4:
		if (!panel_Menu_BeginPlay->getIsRendered()) { panel_Menu_BeginPlay->setIsRendered(true); }

		if (panel_Gameplay->getIsRendered()) { panel_Gameplay->setIsRendered(false); }
		if (panel_Menu_Pause->getIsRendered()) { panel_Menu_Pause->setIsRendered(false); }
		if (panel_Menu_Win->getIsRendered()) { panel_Menu_Win->setIsRendered(false); }
		if (panel_Menu_Lose->getIsRendered()) { panel_Menu_Lose->setIsRendered(false); }
		break;
	}

	if (menuState == 0) { // If A Menu Is Open, The Game Is Paused (No Entity Updates)
		for (int i = 0; i < health; i++) { 
			//balls[i]->CalculateCollisions(balls);
			//balls[i]->Update(deltaTime); 
		}

		//UpdateTime(deltaTime);
	}
}

void TestLevel::UpdateHealth(int diff) {
	std::cout << "Update Health" << std::endl;

	health = (health + diff > maxHealth)? maxHealth: health + diff; // cap health to max

	// Game State Check (Health). Open Game Over Menu
	if (health < 0) { menuState = 3; }

	std::string imageEnabled_Health[maxHealth] = {};
	for (int i = 0; i < maxHealth; i++) {
		if(i < health){
			imageEnabled_Health[i] = ("Health_Icon" + std::to_string(i));
		} else {
			imageEnabled_Health[i] = "";
		}
	}
	panel_Gameplay->EnableImageGroup("Health_Icon", imageEnabled_Health, maxHealth);
}

void TestLevel::UpdateTime(const float deltaTime) {
	timeremaining -= deltaTime;
	
#pragma region Time Texture Sequence Asign
	int sec = ((int)round(timeremaining) % 60);
	int min = (((int)round(timeremaining) - sec) / 60);
	int x = 0; int y = 0; int z = 0; int w = 0;

	if (min < 10) { y = min; }
	else { x = (min - (min % 10)) / 10; y = (min % 10); }
	if (sec < 10) { w = sec; }
	else { z = (sec - (sec % 10)) / 10; w = (sec % 10); }

	int t[4] = { x,y,z,w };


	//std::cout << timeremaining << "\n";
	//std::cout << min << ":" << sec << "\n";
	//std::cout << "T = (" << t[0] << "," << t[1] << "," << t[2] << "," << t[3] << ")\n";
	//std::cout << "-----------------------------------------------------" << "\n";


	for (int i = 0; i < 4; i++) {
		int j = t[i];
		for (int k = 0; k < panel_Gameplay->imageArraylegnth; k++) {
			if (panel_Gameplay->images[k].getName() == ("Time_Icon" + std::to_string(i))) {
				panel_Gameplay->images[k].setTexture(PTRs_Textures_Time[j]);
			}
		}
	}
#pragma endregion

	// Game State Check (Time). Open Game Over Menu
	if (timeremaining <= 0.0f) { menuState = 3; }

}

void TestLevel::HandleEvents(const SDL_Event& sdlEvent) {
#pragma region Debug
	SDL_Event event = sdlEvent;
	if (SDL_PollEvent(&event) == 1) {
		if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.keysym.scancode == SDL_SCANCODE_0) { menuState = 0; }
		if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.keysym.scancode == SDL_SCANCODE_1) { menuState = 1; }
		if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.keysym.scancode == SDL_SCANCODE_2) { menuState = 2; }
		if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.keysym.scancode == SDL_SCANCODE_3) { menuState = 3; }
		if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.keysym.scancode == SDL_SCANCODE_4) { menuState = 4; }
		if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.keysym.scancode == SDL_SCANCODE_EQUALS) { UpdateHealth(1); }
		if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.keysym.scancode == SDL_SCANCODE_MINUS) { UpdateHealth(-1); }
	}
#pragma endregion

	if (sdlEvent.type == SDL_EventType::SDL_MOUSEBUTTONDOWN) { // Debug Mouse Coord On Click
		//Vec2 mouseCoords = Vec2(); mouseCoords.x = sdlEvent.button.x; mouseCoords.y = sdlEvent.button.y;
		//std::cout << "Mouse Coords vec2( " << mouseCoords.x << ", " << mouseCoords.y << ") \n";

		panel_Gameplay->HandleEvents(sdlEvent);
		panel_Menu_BeginPlay->HandleEvents(sdlEvent);
		panel_Menu_Pause->HandleEvents(sdlEvent);
		panel_Menu_Win->HandleEvents(sdlEvent);
		panel_Menu_Lose->HandleEvents(sdlEvent);
	}
	

	#pragma region Begin Play
	if (menuState == 4 && (sdlEvent.key.keysym.scancode == SDL_SCANCODE_SPACE)) {
		menuState = 0;
		// Activate Starting Ball
	}
	#pragma endregion

	#pragma region Menus
	//// If ((The Esc Key is Pushed) && The No Menu Is Open)? Open Esc Menu : Otherwise (If Esc Menu Is Open)? Close Esc Menu : Otherwise Leave Current Menu Open (This Way, You Don't close The Win/Lose Menu)     
	//menuState = (sdlEvent.key.keysym.scancode == SDL_SCANCODE_ESCAPE) ? (menuState == 0)? 1 : (menuState == 1)? 0: menuState : menuState;
	///*if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
	//	if (menuState == 0) {
	//		menuState = 1;
	//	}
	//	else if (menuState == 1) {
	//		menuState = 0;
	//	}
	//}*/
	//

	//// Menu Interaction
	//if (sdlEvent.type == SDL_EventType::SDL_MOUSEBUTTONDOWN && menuState != 0) {

	//	Vec2 mouseCoords = Vec2(); mouseCoords.x = sdlEvent.button.x; mouseCoords.y = sdlEvent.button.y;
	//	Vec3 StoP = MMath::viewToWorldCoord(mouseCoords, screenWidth, screenHeight, camera->getProjectionMatrix(), camera->getViewMatrix());
	//	//std::cout << "Mouse Coords vec2( " << mouseCoords.x << ", " << mouseCoords.y << ") |    |" << "World Coords vec3( " << StoP.x << ", " << StoP.y << ", " << StoP.z << " ) \n";
	//	
	//	// Check which button, if any, the cousor is on
	//	int buttonPressed = 0;

	//	switch (menuState) {
	//	case 1:
	//		if		(StoP.x <= Esc_button_Resume_bounds.x		 && StoP.y <= Esc_button_Resume_bounds.y		&& StoP.x >= Esc_button_Resume_bounds.z		   && StoP.y >= Esc_button_Resume_bounds.w		 ) { buttonPressed = 1; }
	//		else if (StoP.x <= Esc_button_Replay_bounds.x		 && StoP.y <= Esc_button_Replay_bounds.y		&& StoP.x >= Esc_button_Replay_bounds.z		   && StoP.y >= Esc_button_Replay_bounds.w		 ) { buttonPressed = 2; }
	//		else if (StoP.x <= Esc_button_QuitToMenu_bounds.x	 && StoP.y <= Esc_button_QuitToMenu_bounds.y	&& StoP.x >= Esc_button_QuitToMenu_bounds.z	   && StoP.y >= Esc_button_QuitToMenu_bounds.w	 ) { buttonPressed = 3; }
	//		else if (StoP.x <= Esc_button_QuitToDesktop_bounds.x && StoP.y <= Esc_button_QuitToDesktop_bounds.y && StoP.x >= Esc_button_QuitToDesktop_bounds.z && StoP.y >= Esc_button_QuitToDesktop_bounds.w) { buttonPressed = 4; }

	//		break;
	//	case 2:
	//		if      (StoP.x <= Win_button_Replay_bounds.x		 && StoP.y <= Win_button_Replay_bounds.y		&& StoP.x >= Win_button_Replay_bounds.z		   && StoP.y >= Win_button_Replay_bounds.w		 ) { buttonPressed = 2; }
	//		else if (StoP.x <= Win_button_QuitToMenu_bounds.x	 && StoP.y <= Win_button_QuitToMenu_bounds.y	&& StoP.x >= Win_button_QuitToMenu_bounds.z	   && StoP.y >= Win_button_QuitToMenu_bounds.w	 ) { buttonPressed = 3; }
	//		else if (StoP.x <= Win_button_QuitToDesktop_bounds.x && StoP.y <= Win_button_QuitToDesktop_bounds.y && StoP.x >= Win_button_QuitToDesktop_bounds.z && StoP.y >= Win_button_QuitToDesktop_bounds.w) { buttonPressed = 4; }

	//		break;
	//	case 3:
	//		if		(StoP.x <= Lose_button_Replay_bounds.x		  && StoP.y <= Lose_button_Replay_bounds.y		  && StoP.x >= Lose_button_Replay_bounds.z		  && StoP.y >= Lose_button_Replay_bounds.w		 ) { buttonPressed = 2; }
	//		else if (StoP.x <= Lose_button_QuitToMenu_bounds.x	  && StoP.y <= Lose_button_QuitToMenu_bounds.y	  && StoP.x >= Lose_button_QuitToMenu_bounds.z	  && StoP.y >= Lose_button_QuitToMenu_bounds.w	 ) { buttonPressed = 3; }
	//		else if (StoP.x <= Lose_button_QuitToDesktop_bounds.x && StoP.y <= Lose_button_QuitToDesktop_bounds.y && StoP.x >= Lose_button_QuitToDesktop_bounds.z && StoP.y >= Lose_button_QuitToDesktop_bounds.w) { buttonPressed = 4; }

	//		break;
	//	default:
	//		break;
	//	}
	//	
	//	// Change Current Call Designation To Have The Scene Manager Change Scene
	//	// See Line 67 In SceneManager
	//	switch (buttonPressed) {
	//	case 0:
	//		std::cout << "No Button Pressed" << "\n";
	//		break;

	//	case 1:
	//		std::cout << "Resume" << "\n";
	//		menuState = 0;
	//		break;

	//	case 2:
	//		std::cout << "Replay" << "\n";
	//		callDesignation = myDesignation;
	//		break;

	//	case 3:
	//		std::cout << "Quit To Menu" << "\n";
	//		callDesignation = 0;
	//		break;
	//	case 4:
	//		std::cout << "Quit To Desktop" << "\n";
	//		callDesignation = -1;
	//		break;
	//	}
	//}
	#pragma endregion

	#pragma region Paddle
	if (menuState == 0) { // If The Game Is Not Paused
		int paddleDir = -1; // -1 = None, 0 = Left, 1 = Right, 2 = Both
		if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.keysym.scancode == SDL_SCANCODE_LEFT) {
			paddleDir = 0;
		}
		else if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
			// If The Left Arrow Was Not Pressed, Activate Only Right Paddles. Otherwiase, Activate All Paddles
			paddleDir = (paddleDir == -1) ? 1 : 2;
			
		}

		
		/*
		for (int i = 0; i < paddles.legth; i++) {
			switch (paddleDir) {
			case 0:
				if (paddles[i]->GetDirection() == 0) { paddles[i]->Activate(); } // Activate Only Left Paddles
				break;
			case 1:
				if (paddles[i]->GetDirection() == 1) { paddles[i]->Activate(); } // Activate Only Right Paddles
				break;
			case 0:
				paddles[i]->Activate(); // Activate All Paddles
				break;
			default:
				break;
			}
		}
		*/
	}
	#pragma endregion

}

void TestLevel::Render() const {
	glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);


	#pragma region UI Render
	GLuint Program_Menu = panel_Menu_Pause->getShader()->getProgram();
	glUseProgram(Program_Menu);

	glUniformMatrix4fv(panel_Menu_Pause->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
	glUniformMatrix4fv(panel_Menu_Pause->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix());
	glUniform3fv(panel_Menu_Pause->getShader()->getUniformID("lightPos"), 1, lightSource_UI);

	panel_Gameplay->Render();
	panel_Menu_BeginPlay->Render();
	panel_Menu_Pause->Render();
	panel_Menu_Win->Render();
	panel_Menu_Lose->Render();

	//if (menuState == 0) {
	//	// Renders same number of icons as health. Starts at index=0 so health bar moves from left to right
	//	// [] [] [] :: ::  <- health = 3/5
	//	for (int i = 0; i < health; i++) {
	//		healthUI[i]->Render();
	//	}
	//	for (int i = 0; i < 4; i++) {
	//		timeUI[i]->Render();
	//	}
	//}
	#pragma endregion

	#pragma region Entitiy Render
	/*if (menuState == 0) {
		GLuint Program_Entity = balls[0]->getShader()->getProgram();
		glUseProgram(Program_Entity);

		glUniformMatrix4fv(balls[0]->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
		glUniformMatrix4fv(balls[0]->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix());
		glUniform3fv(balls[0]->getShader()->getUniformID("lightPos"), 1, lightSource_UI);

		for (int i = 0; i < maxHealth; i++) { balls[i]->Render(); }
	}*/
	#pragma endregion

	glUseProgram(0);
}

void TestLevel::OnDestroy() {
	//if (meshPtr) delete meshPtr, meshPtr = nullptr;
}
