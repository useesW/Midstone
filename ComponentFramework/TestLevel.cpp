#include <glew.h>
#include <SDL.h>
#include <iostream>
#include "Debug.h"
#include "MMath.h"
#include "Physics.h"
#include "ObjLoader.h"
#include "TestLevel.h"
#include "Camera.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "UIObject.h"
#include "Pinball.h"

TestLevel::TestLevel() : camera(nullptr) {
	camera = new Camera;
	Debug::Info("Created MainMenu: ", __FILE__, __LINE__);
}

TestLevel::~TestLevel() {}

bool TestLevel::OnCreate() {

	lightSource_UI = Vec3(0.0f, 0.0f, 0.0f);

	#pragma region UI
	UI_shaderPtr = new Shader("shaders/texturePhongVert.glsl", "shaders/texturePhongFrag.glsl");
	if (UI_shaderPtr == nullptr) { Debug::FatalError("Couldn't create UI Shader", __FILE__, __LINE__); return false; } // Shader Initialization Check

	float BeginPlayScaleFactor = 0.46f;
	float MenuScaleFactor = 0.46f;

	#pragma region Begin Play
	// Load Begin Play Mesh
	if (ObjLoader::loadOBJ("meshes/Menu_Background.obj") == false) { Debug::FatalError("Couldn't load Begin Play object", __FILE__, __LINE__); return false; }
	beginPlayUI_meshPtr = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);


	// Load Begin Play Texture
	beginPlayUI_texturePtr = new Texture();
	if (beginPlayUI_texturePtr->LoadImage("textures/PauseMenuTransparent.png") == false) { Debug::FatalError("Couldn't load Begin Play texture", __FILE__, __LINE__); return false; }


	// Asset Pointer Check
	if (beginPlayUI_meshPtr == nullptr || beginPlayUI_texturePtr == nullptr) { Debug::FatalError("Couldn't create Begin Play assets", __FILE__, __LINE__); return false; }


	// Begin Play Initialization
	beginPlayUI = new UIObject(beginPlayUI_meshPtr, UI_shaderPtr, beginPlayUI_texturePtr);
	if (beginPlayUI == nullptr) { Debug::FatalError("Begin Play could not be initialized", __FILE__, __LINE__); return false; }

	
	beginPlayUI->setModelMatrix(MMath::scale(Vec3(16.0 * BeginPlayScaleFactor, 9.0 * BeginPlayScaleFactor, 1.0)) * MMath::rotate(180, Vec3(0.0f, 0.0f, 1.0f)));
	#pragma endregion

	#pragma region Menu (Esc)
	// Load Menu (Esc) Mesh
	if (ObjLoader::loadOBJ("meshes/Menu_Background.obj") == false) { Debug::FatalError("Couldn't load menu (Esc) object", __FILE__, __LINE__); return false; }
	menu_Esc_meshPtr = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);


	// Load Menu (Esc) Texture
	menu_Esc_texturePtr = new Texture();
	if (menu_Esc_texturePtr->LoadImage("textures/PauseMenu.png") == false) { Debug::FatalError("Couldn't load menu (Esc) texture", __FILE__, __LINE__); return false; }


	// Asset Pointer Check
	if (menu_Esc_meshPtr == nullptr || menu_Esc_texturePtr == nullptr) { Debug::FatalError("Couldn't create menu (Esc) assets", __FILE__, __LINE__); return false; }


	// Menu (Esc) Initialization
	menuUI_Esc = new UIObject(menu_Esc_meshPtr, UI_shaderPtr, menu_Esc_texturePtr);
	if (menuUI_Esc == nullptr) { Debug::FatalError("Menu (Esc) could not be initialized", __FILE__, __LINE__); return false; }

	menuUI_Esc->setModelMatrix(MMath::scale(Vec3(16.0 * MenuScaleFactor, 9.0 * MenuScaleFactor, 1.0)) * MMath::rotate(180, Vec3(0.0f, 0.0f, 1.0f)));
	#pragma endregion

	#pragma region Menu (Win)
	// Load Menu (Win) Mesh
	if (ObjLoader::loadOBJ("meshes/Menu_Background.obj") == false) { Debug::FatalError("Couldn't load menu (Win) object", __FILE__, __LINE__); return false; }
	menu_Win_meshPtr = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);


	// Load Menu (Win) Texture
	menu_Win_texturePtr = new Texture();
	if (menu_Win_texturePtr->LoadImage("textures/WinMenu.png") == false) { Debug::FatalError("Couldn't load menu (Win) texture", __FILE__, __LINE__); return false; }


	// Asset Pointer Check
	if (menu_Win_meshPtr == nullptr || menu_Win_texturePtr == nullptr) { Debug::FatalError("Couldn't create menu (Win) assets", __FILE__, __LINE__); return false; }


	// Menu (Win) Initialization
	menuUI_Win = new UIObject(menu_Win_meshPtr, UI_shaderPtr, menu_Win_texturePtr);
	if (menuUI_Win == nullptr) { Debug::FatalError("Menu (Win) could not be initialized", __FILE__, __LINE__); return false; }

	menuUI_Win->setModelMatrix(MMath::scale(Vec3(16.0 * MenuScaleFactor, 9.0 * MenuScaleFactor, 1.0)) * MMath::rotate(180, Vec3(0.0f, 0.0f, 1.0f)));
	#pragma endregion

	#pragma region Menu (Lose)
	// Load Menu (Lose) Mesh
	if (ObjLoader::loadOBJ("meshes/Menu_Background.obj") == false) { Debug::FatalError("Couldn't load menu (Lose) object", __FILE__, __LINE__); return false; }
	menu_Lose_meshPtr = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);


	// Load Menu (Lose) Texture
	menu_Lose_texturePtr = new Texture();
	if (menu_Lose_texturePtr->LoadImage("textures/LoseMenu.png") == false) { Debug::FatalError("Couldn't load menu (Lose) texture", __FILE__, __LINE__); return false; }


	// Asset Pointer Check
	if (menu_Lose_meshPtr == nullptr || menu_Lose_texturePtr == nullptr) { Debug::FatalError("Couldn't create menu (Lose) assets", __FILE__, __LINE__); return false; }


	// Menu (Lose) Initialization
	menuUI_Lose = new UIObject(menu_Lose_meshPtr, UI_shaderPtr, menu_Lose_texturePtr);
	if (menuUI_Lose == nullptr) { Debug::FatalError("Menu (Lose) could not be initialized", __FILE__, __LINE__); return false; }

	menuUI_Lose->setModelMatrix(MMath::scale(Vec3(16.0 * MenuScaleFactor, 9.0 * MenuScaleFactor, 1.0)) * MMath::rotate(180, Vec3(0.0f, 0.0f, 1.0f)));
	#pragma endregion

	#pragma region Buttons
	Esc_button_Resume_bounds = Vec4(0.123113, 0.201354, -0.123113, 0.113909);
	Esc_button_Replay_bounds = Vec4(0.112758, 0.0770898, -0.120812, -0.00805415);
	Esc_button_QuitToMenu_bounds = Vec4(0.231269, -0.0437226, -0.23357, -0.134619);
	Esc_button_QuitToDesktop_bounds = Vec4(0.298004, -0.178342, -0.283046, -0.269239);

	Win_button_Replay_bounds = Vec4(0.118511, 0.170288, -0.11621, 0.0851439);
	Win_button_QuitToMenu_bounds = Vec4(0.240474, 0.0149577, -0.226667, -0.0759392);
	Win_button_QuitToDesktop_bounds = Vec4(0.298004, -0.147276, -0.283046, -0.237022);

	Lose_button_Replay_bounds = Win_button_Replay_bounds;
	Lose_button_QuitToMenu_bounds = Win_button_QuitToMenu_bounds; 
	Lose_button_QuitToDesktop_bounds = Win_button_QuitToDesktop_bounds;
	#pragma endregion


	#pragma region Health Bar
	// Load Health UI Mesh
	if (ObjLoader::loadOBJ("meshes/Menu_Background.obj") == false) { Debug::FatalError("Couldn't load healthUI object", __FILE__, __LINE__); return false; }
	healthUI_meshPtr = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);


	// Load Health UI Texture
	healthUI_texturePtr = new Texture();
	if (healthUI_texturePtr->LoadImage("textures/heart.png") == false) { Debug::FatalError("Couldn't load healthUI texture", __FILE__, __LINE__); return false; }


	// Asset Pointer Check
	if (healthUI_meshPtr == nullptr || healthUI_texturePtr == nullptr) { Debug::FatalError("Couldn't create healthUI assets", __FILE__, __LINE__); return false; }

	// Health UI Initialization
	const float healthBarOffset = 0.6f;
	float currentOffset = -7.0f;

	for (int i = 0; i < maxHealth; i++) {
		healthUI[i] = new UIObject(healthUI_meshPtr, UI_shaderPtr, healthUI_texturePtr);

		if (healthUI[i] == nullptr) {
			Debug::FatalError("healthUI [" + std::to_string(i) + "] could not be initialized", __FILE__, __LINE__); return false;
		}

		healthUI[i]->setModelMatrix(
			// ***CHANGE Y & Z COMPONENTS * **
			MMath::translate(Vec3(currentOffset, -3.8f, 0.f)) * // Iterates on offset to make sure health icons are spaced apart
			MMath::scale(Vec3(0.3f, 0.3f, 1.0)) * // Identical scales for each
			MMath::rotate(180, Vec3(0.0f, 0.0f, 1.0f))); // face the camera

		currentOffset += healthBarOffset;
	}

	#pragma endregion

	//return true;

	#pragma region Time Display
	// Load Time UI Mesh
	if (ObjLoader::loadOBJ("meshes/Menu_Background.obj") == false) { Debug::FatalError("Couldn't load timeUI object", __FILE__, __LINE__); return false; }
	timeUI_meshPtr = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);


	// Load Health UI Texture
	for (int i = 0; i < 10; i++) {
		timeUI_texturePtr[i] = new Texture();
		if (timeUI_texturePtr[i]->LoadImage(("textures/number" + std::to_string(i) + ".jpg").c_str()) == false) { Debug::FatalError("Couldn't load timeUI #" + std::to_string(i) + " texture", __FILE__, __LINE__); return false; }
		
		//Remove once number images are added to project
		//if (timeUI_texturePtr[i]->LoadImage("textures/MenuPage.png") == false) { Debug::FatalError("Couldn't load timeUI #" + std::to_string(i) + " texture", __FILE__, __LINE__); return false; }
	}


	// Asset Pointer Check
	if (timeUI_meshPtr == nullptr || timeUI_texturePtr[0] == nullptr) { Debug::FatalError("Couldn't create timeUI assets", __FILE__, __LINE__); return false; }

	// Time UI Initialization
	const float timeBarOffset = 0.9f;
	currentOffset = 4.2f;
	
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

	

	for (int i = 0; i < 4; i++) {
		int j = t[i];
		//std::cout << j << ",";
		timeUI[i] = new UIObject(timeUI_meshPtr, UI_shaderPtr, timeUI_texturePtr[j]);

		if (timeUI[i] == nullptr) {
			std::string Elog = "timeUI [";	Elog += i;	Elog += "] could not be initialized";
			Debug::FatalError(Elog, __FILE__, __LINE__); return false;
		}

		timeUI[i]->setModelMatrix(
			// ***CHANGE Y & Z COMPONENTS * **
			MMath::translate(Vec3(currentOffset, -3.7f, 0.f)) * // Iterates on offset to make sure health icons are spaced apart
			MMath::scale(Vec3(0.4f, 0.4f, 1.0)) * // Identical scales for each
			MMath::rotate(180, Vec3(0.0f, 0.0f, 1.0f))); // face the camera

		currentOffset += timeBarOffset;
	}
	#pragma endregion

	#pragma endregion


	#pragma region Entities
	
	#pragma region Balls
	// Load PinBall Mesh
	if (ObjLoader::loadOBJ("meshes/Menu_Background.obj") == false) { Debug::FatalError("Couldn't load PinBall object", __FILE__, __LINE__); return false; }
	ball_meshPtr = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);
	
	// Load PinBall Texture
	ball_texturePtr = new Texture();
	if (ball_texturePtr->LoadImage("textures/CreditButton.png") == false) { Debug::FatalError("Couldn't load PinBall texture", __FILE__, __LINE__); return false; }


	// Asset Pointer Check
	if (ball_meshPtr == nullptr || ball_texturePtr == nullptr) { Debug::FatalError("Couldn't create PinBall assets", __FILE__, __LINE__); return false; }

	// PinBall Initialization

	Vec3 randpos[] = {Vec3(0,0,0), Vec3(2,2,0),Vec3(-2,1,0) ,Vec3(3,2,0) ,Vec3(-1,-3,0) };
	Vec3 randvel[] = {Vec3(0.1,0.5,0), Vec3(0.2,0.1,0),Vec3(0.7,0.3,0) ,Vec3(0.3,0.4,0) ,Vec3(0.1,0.3,0) };

	for (int i = 0; i < maxHealth; i++) {
		balls[i] = new PinBall(ball_meshPtr, UI_shaderPtr, ball_texturePtr);
		if (balls[i] == nullptr) {
			Debug::FatalError("PinBall [" + std::to_string(i) + "] could not be initialized", __FILE__, __LINE__); return false;
		}

		balls[i]->setPos(randpos[i]);
		balls[i]->setVel(randvel[i]);
	}
	#pragma endregion

	#pragma endregion


	#pragma region Garbage Collection
	// There Is More
	//delete t;
	#pragma endregion

	return true;
}



void TestLevel::Update(const float deltaTime) {
	//std::cout << menuState << "\n";
	if (menuState == 0) { // If A Menu Is Open, The Game Is Paused (No Entity Updates)
		// Update all entites
		//std::cout << "Start Collision Calculations For Balls __________________________________________________________________________________________________ \n";
		for (int i = 0; i < health; i++) { 
			/*std::cout << "Start Collision Calculations For Ball: " << i << "--------------------------------------------------------------\n";
			balls[i]->CalculateCollisions(balls);
			std::cout << "End Collision Calculations For Ball: " << i << "--------------------------------------------------------------\n";*/

			balls[i]->Update(deltaTime); 
			// std::cout << balls[i]->getPos().x << "'" << balls[i]->getPos().x << "\n";
		}
		//std::cout << "End Collision Calculations For Balls __________________________________________________________________________________________________ \n";

		UpdateTime(deltaTime);
	}
}


void TestLevel::UpdateHealth(int diff) {
	health = (health + diff > maxHealth)? maxHealth: health + diff; // cap health to max

	// Game State Check (Health). Open Game Over Menu
	if (health < 0) { menuState = 3; }
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
		Matrix4 tempMat = timeUI[i]->getModelMatrix();
		timeUI[i] = new UIObject(timeUI_meshPtr, UI_shaderPtr, timeUI_texturePtr[j]);
		timeUI[i]->setModelMatrix(tempMat);
	}
	#pragma endregion


	// Game State Check (Time). Open Game Over Menu
	if (timeremaining <= 0.0f) { menuState = 3; }

}

void TestLevel::HandleEvents(const SDL_Event& sdlEvent) {
	
	#pragma region Debug
	SDL_Event event = sdlEvent;
	if (SDL_PollEvent(&event) == 1) {
		if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.keysym.scancode == SDL_SCANCODE_E) { menuState = 1; }
		if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.keysym.scancode == SDL_SCANCODE_W) { menuState = 2; }
		if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.keysym.scancode == SDL_SCANCODE_L) { menuState = 3; }
		if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.keysym.scancode == SDL_SCANCODE_EQUALS) { UpdateHealth(1); }
		if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.keysym.scancode == SDL_SCANCODE_MINUS) { UpdateHealth(-1); }
	}
	#pragma endregion



	#pragma region Begin Play
	if (menuState == 4 && (sdlEvent.key.keysym.scancode == SDL_SCANCODE_SPACE)) {
		menuState = 0;
		// Activate Starting Ball
	}
	#pragma endregion

	#pragma region Menus
	// If ((The Esc Key is Pushed) && The No Menu Is Open)? Open Esc Menu : Otherwise (If Esc Menu Is Open)? Close Esc Menu : Otherwise Leave Current Menu Open (This Way, You Don't close The Win/Lose Menu)     
	menuState = (sdlEvent.key.keysym.scancode == SDL_SCANCODE_ESCAPE) ? (menuState == 0)? 1 : (menuState == 1)? 0: menuState : menuState;
	/*if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_ESCAPE) {
		if (menuState == 0) {
			menuState = 1;
		}
		else if (menuState == 1) {
			menuState = 0;
		}
	}*/
	

	// Menu Interaction
	if (sdlEvent.type == SDL_EventType::SDL_MOUSEBUTTONDOWN && menuState != 0) {

		Vec2 mouseCoords = Vec2(); mouseCoords.x = sdlEvent.button.x; mouseCoords.y = sdlEvent.button.y;
		Vec3 StoP = MMath::viewToWorldCoord(mouseCoords, screenWidth, screenHeight, camera->getProjectionMatrix(), camera->getViewMatrix());
		//std::cout << "Mouse Coords vec2( " << mouseCoords.x << ", " << mouseCoords.y << ") |    |" << "World Coords vec3( " << StoP.x << ", " << StoP.y << ", " << StoP.z << " ) \n";
		
		// Check which button, if any, the cousor is on
		int buttonPressed = 0;

		switch (menuState) {
		case 1:
			if		(StoP.x <= Esc_button_Resume_bounds.x		 && StoP.y <= Esc_button_Resume_bounds.y		&& StoP.x >= Esc_button_Resume_bounds.z		   && StoP.y >= Esc_button_Resume_bounds.w		 ) { buttonPressed = 1; }
			else if (StoP.x <= Esc_button_Replay_bounds.x		 && StoP.y <= Esc_button_Replay_bounds.y		&& StoP.x >= Esc_button_Replay_bounds.z		   && StoP.y >= Esc_button_Replay_bounds.w		 ) { buttonPressed = 2; }
			else if (StoP.x <= Esc_button_QuitToMenu_bounds.x	 && StoP.y <= Esc_button_QuitToMenu_bounds.y	&& StoP.x >= Esc_button_QuitToMenu_bounds.z	   && StoP.y >= Esc_button_QuitToMenu_bounds.w	 ) { buttonPressed = 3; }
			else if (StoP.x <= Esc_button_QuitToDesktop_bounds.x && StoP.y <= Esc_button_QuitToDesktop_bounds.y && StoP.x >= Esc_button_QuitToDesktop_bounds.z && StoP.y >= Esc_button_QuitToDesktop_bounds.w) { buttonPressed = 4; }

			break;
		case 2:
			if      (StoP.x <= Win_button_Replay_bounds.x		 && StoP.y <= Win_button_Replay_bounds.y		&& StoP.x >= Win_button_Replay_bounds.z		   && StoP.y >= Win_button_Replay_bounds.w		 ) { buttonPressed = 2; }
			else if (StoP.x <= Win_button_QuitToMenu_bounds.x	 && StoP.y <= Win_button_QuitToMenu_bounds.y	&& StoP.x >= Win_button_QuitToMenu_bounds.z	   && StoP.y >= Win_button_QuitToMenu_bounds.w	 ) { buttonPressed = 3; }
			else if (StoP.x <= Win_button_QuitToDesktop_bounds.x && StoP.y <= Win_button_QuitToDesktop_bounds.y && StoP.x >= Win_button_QuitToDesktop_bounds.z && StoP.y >= Win_button_QuitToDesktop_bounds.w) { buttonPressed = 4; }

			break;
		case 3:
			if		(StoP.x <= Lose_button_Replay_bounds.x		  && StoP.y <= Lose_button_Replay_bounds.y		  && StoP.x >= Lose_button_Replay_bounds.z		  && StoP.y >= Lose_button_Replay_bounds.w		 ) { buttonPressed = 2; }
			else if (StoP.x <= Lose_button_QuitToMenu_bounds.x	  && StoP.y <= Lose_button_QuitToMenu_bounds.y	  && StoP.x >= Lose_button_QuitToMenu_bounds.z	  && StoP.y >= Lose_button_QuitToMenu_bounds.w	 ) { buttonPressed = 3; }
			else if (StoP.x <= Lose_button_QuitToDesktop_bounds.x && StoP.y <= Lose_button_QuitToDesktop_bounds.y && StoP.x >= Lose_button_QuitToDesktop_bounds.z && StoP.y >= Lose_button_QuitToDesktop_bounds.w) { buttonPressed = 4; }

			break;
		default:
			break;
		}
		
		// Change Current Call Designation To Have The Scene Manager Change Scene
		// See Line 67 In SceneManager
		switch (buttonPressed) {
		case 0:
			std::cout << "No Button Pressed" << "\n";
			break;

		case 1:
			std::cout << "Resume" << "\n";
			menuState = 0;
			break;

		case 2:
			std::cout << "Replay" << "\n";
			callDesignation = myDesignation;
			break;

		case 3:
			std::cout << "Quit To Menu" << "\n";
			callDesignation = 0;
			break;
		case 4:
			std::cout << "Quit To Desktop" << "\n";
			callDesignation = -1;
			break;
		}
	}
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
	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);


	// Draw Scene
	#pragma region UI Render
	GLuint Program_Menu = menuUI_Esc->getShader()->getProgram();
	glUseProgram(Program_Menu);

	glUniformMatrix4fv(menuUI_Esc->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
	glUniformMatrix4fv(menuUI_Esc->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix());
	glUniform3fv(menuUI_Esc->getShader()->getUniformID("lightPos"), 1, lightSource_UI);

	// Render Opened Menu, If Any
	switch (menuState) {
	case 1:
		menuUI_Esc->Render();
		break;
	case 2:
		menuUI_Win->Render();
		break;
	case 3:
		menuUI_Lose->Render();
		break;
	case 4:
		beginPlayUI->Render();
		break;
	default:
		break;
	}

	// Renders same number of icons as health. Starts at index=0 so health bar moves from left to right
	// [] [] [] :: ::  <- health = 3/5
	for (int i = 0; i < health; i++) {
		healthUI[i]->Render();
	}
	for (int i = 0; i < 4; i++) {
		timeUI[i]->Render();
	}
	#pragma endregion

	#pragma region Entitiy Render
	GLuint Program_Entity = balls[0]->getShader()->getProgram();
	glUseProgram(Program_Entity);

	glUniformMatrix4fv(balls[0]->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
	glUniformMatrix4fv(balls[0]->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix());
	glUniform3fv(balls[0]->getShader()->getUniformID("lightPos"), 1, lightSource_UI);

	for (int i = 0; i < maxHealth; i++) { balls[i]->Render(); }

	#pragma endregion

	glUseProgram(0);
}


void TestLevel::OnDestroy() {
	//if (meshPtr) delete meshPtr, meshPtr = nullptr;
}
