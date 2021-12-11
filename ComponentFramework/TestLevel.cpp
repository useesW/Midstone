#include "TestLevel.h"
#include <glew.h>
#include <SDL.h>
#include <iostream>
#include "Debug.h"
#include "MMath.h"

#include "ObjLoader.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

#include "Camera.h"
#include "UIObject.h"
#include "Physics.h"
#include "Pinball.h"
#include "Paddle.h"
#include "Affector.h"
#include "Goal.h"

TestLevel::TestLevel() : camera(nullptr) {
	camera = new Camera;
	lightSource_UI = Vec3(0.0f, 0.0f, 0.0f);
	Debug::Info("Created MainMenu: ", __FILE__, __LINE__);
}

TestLevel::~TestLevel() {}

bool TestLevel::OnCreate() {
#pragma region UI
	UI_shaderPtr = new Shader("shaders/texturePhongVert.glsl", "shaders/texturePhongFrag.glsl");
	if (UI_shaderPtr == nullptr) { Debug::FatalError("Couldn't Create UI Shader", __FILE__, __LINE__); return false; } // Shader Initialization Check

	if (ObjLoader::loadOBJ("meshes/Menu_Background.obj") == false) { Debug::FatalError("Couldn't Load UI Mesh", __FILE__, __LINE__); return false; }
	UI_meshPtr = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);

	float UIPanelScaleFactor = 0.46f;

#pragma region Begin Play
	// Load Begin Play Texture
	beginPlayUI_texturePtr = new Texture();
	if (beginPlayUI_texturePtr->LoadImage("textures/SpaceBar_Play.png") == false) { Debug::FatalError("Couldn't Load Begin Play Texture", __FILE__, __LINE__); return false; }

	// Begin Play Initialization
	beginPlayUI = new UIObject(UI_meshPtr, UI_shaderPtr, beginPlayUI_texturePtr);
	if (beginPlayUI == nullptr) { Debug::FatalError("Begin Play Could Not Be Initialized", __FILE__, __LINE__); return false; }

	beginPlayUI->setModelMatrix(MMath::scale(Vec3(9.0 * UIPanelScaleFactor, 1.0 * UIPanelScaleFactor, 1.0)) * MMath::rotate(180, Vec3(0.0f, 0.0f, 1.0f)));
#pragma endregion

#pragma region Gameplay UI
	// Load Begin Play Texture
	gameplayUI_texturePtr = new Texture();
	if (gameplayUI_texturePtr->LoadImage("textures/Default_Background.png") == false) { Debug::FatalError("Couldn't Load Gameplay Texture", __FILE__, __LINE__); return false; }

	// Begin Play Initialization
	gameplayUI = new UIObject(UI_meshPtr, UI_shaderPtr, gameplayUI_texturePtr);
	if (gameplayUI == nullptr) { Debug::FatalError("Begin Play Could Not Be Initialized", __FILE__, __LINE__); return false; }

	gameplayUI->setModelMatrix(MMath::scale(Vec3(16.0 * UIPanelScaleFactor, 9.0 * UIPanelScaleFactor, 1.0)) * MMath::rotate(180, Vec3(0.0f, 0.0f, 1.0f)));
#pragma endregion

#pragma region Menu (Esc)
	// Load Menu (Esc) Texture
	menu_Pause_texturePtr = new Texture();
	if (menu_Pause_texturePtr->LoadImage("textures/Menu_Pause.png") == false) { Debug::FatalError("Couldn't Load Pause Menu Texture", __FILE__, __LINE__); return false; }

	// Menu (Esc) Initialization
	menuUI_Pause = new UIObject(UI_meshPtr, UI_shaderPtr, menu_Pause_texturePtr);
	if (menuUI_Pause == nullptr) { Debug::FatalError("Pause Menu Could Not Be Initialized", __FILE__, __LINE__); return false; }

	menuUI_Pause->setModelMatrix(MMath::scale(Vec3(16.0 * UIPanelScaleFactor, 9.0 * UIPanelScaleFactor, 1.0)) * MMath::rotate(180, Vec3(0.0f, 0.0f, 1.0f)));
#pragma endregion

#pragma region Menu (Win)
	// Load Menu (Win) Texture
	menu_Win_texturePtr = new Texture();
	if (menu_Win_texturePtr->LoadImage("textures/Menu_Win.png") == false) { Debug::FatalError("Couldn't Load Win Menu Texture", __FILE__, __LINE__); return false; }

	// Menu (Win) Initialization
	menuUI_Win = new UIObject(UI_meshPtr, UI_shaderPtr, menu_Win_texturePtr);
	if (menuUI_Win == nullptr) { Debug::FatalError("Win Menu Could Not Be Initialized", __FILE__, __LINE__); return false; }

	menuUI_Win->setModelMatrix(MMath::scale(Vec3(16.0 * UIPanelScaleFactor, 9.0 * UIPanelScaleFactor, 1.0)) * MMath::rotate(180, Vec3(0.0f, 0.0f, 1.0f)));
#pragma endregion

#pragma region Menu (Lose)
	// Load Menu (Lose) Texture
	menu_Lose_texturePtr = new Texture();
	if (menu_Lose_texturePtr->LoadImage("textures/Menu_Lose.png") == false) { Debug::FatalError("Couldn't Load Lose Menu Texture", __FILE__, __LINE__); return false; }

	// Menu (Lose) Initialization
	menuUI_Lose = new UIObject(UI_meshPtr, UI_shaderPtr, menu_Lose_texturePtr);
	if (menuUI_Lose == nullptr) { Debug::FatalError("Lose Menu Could Not Be Initialized", __FILE__, __LINE__); return false; }

	menuUI_Lose->setModelMatrix(MMath::scale(Vec3(16.0 * UIPanelScaleFactor, 9.0 * UIPanelScaleFactor, 1.0)) * MMath::rotate(180, Vec3(0.0f, 0.0f, 1.0f)));
#pragma endregion

#pragma region Buttons
	Pause_button_Resume_bounds = Vec4(0.121963, 0.117361, -0.125415, 0.202504);
	Pause_button_Replay_bounds = Vec4(0.112758, 0.0770898, -0.120812, -0.00805415);
	Pause_button_QuitToMenu_bounds = Vec4(0.231269, -0.0437226, -0.23357, -0.134619);
	Pause_button_QuitToDesktop_bounds = Vec4(0.298004, -0.178342, -0.283046, -0.269239);

	Win_button_Replay_bounds = Vec4(0.118511, 0.170288, -0.11621, 0.0851439);
	Win_button_QuitToMenu_bounds = Vec4(0.240474, 0.0149577, -0.226667, -0.0759392);
	Win_button_QuitToDesktop_bounds = Vec4(0.298004, -0.147276, -0.283046, -0.237022);

	Lose_button_Replay_bounds = Win_button_Replay_bounds;
	Lose_button_QuitToMenu_bounds = Win_button_QuitToMenu_bounds;
	Lose_button_QuitToDesktop_bounds = Win_button_QuitToDesktop_bounds;
#pragma endregion

#pragma region Health Bar
	// Load Health UI Texture
	healthUI_texturePtr = new Texture();
	if (healthUI_texturePtr->LoadImage("textures/UI_Heart.png") == false) { Debug::FatalError("Couldn't Load Health UI Texture", __FILE__, __LINE__); return false; }

	// Health UI Initialization
	const float healthBarOffset = 0.6f;
	float currentOffset = -1.50f;

	for (int i = 0; i < maxHealth; i++) {
		healthUI[i] = new UIObject(UI_meshPtr, UI_shaderPtr, healthUI_texturePtr);
		if (healthUI[i] == nullptr) { Debug::FatalError("Health UI [" + std::to_string(i) + "] Could Not Be Initialized", __FILE__, __LINE__); return false; }

		healthUI[i]->setModelMatrix(
			MMath::translate(Vec3(currentOffset, -3.8f, 0.f)) * // Iterates on offset to make sure health icons are spaced apart
			MMath::scale(Vec3(0.3f, 0.3f, 1.0)) * // Identical scales for each
			MMath::rotate(180, Vec3(0.0f, 0.0f, 1.0f))); // face the camera

		currentOffset += healthBarOffset;
	}
#pragma endregion

#pragma region Time Display
	// Load Timer UI Texture
	for (int i = 0; i <= 11; i++) {
		timeUI_texturePtr[i] = new Texture();
		if (timeUI_texturePtr[i]->LoadImage(("textures/Timer_" + std::to_string(i) + ".png").c_str()) == false) { Debug::FatalError("Couldn't Load Time UI # " + std::to_string(i) + " Texture", __FILE__, __LINE__); return false; }
	}

	// Time UI Initialization
	const float timeBarOffset = 0.3f;
	currentOffset = 2.5f;

#pragma region Time Texture Sequence
	int sec = ((int)timeremaining % 60);
	int min = (((int)timeremaining - sec) / 60);
	int x = 0; int y = 0; int z = 0; int w = 0;

	if (min < 10) { y = min; } else { x = (min - (min % 10)) / 10; y = (min % 10); }
	if (sec < 10) { w = sec; } else { z = (sec - (sec % 10)) / 10; w = (sec % 10); }

	int t[5] = { x, y, 10, z, w };
#pragma endregion

	for (int i = 0; i < 5; i++) {
		int j = t[i];
		//std::cout << j << ",";
		timeUI[i] = new UIObject(UI_meshPtr, UI_shaderPtr, timeUI_texturePtr[j]);

		if (timeUI[i] == nullptr) { Debug::FatalError("Time UI [ " + std::to_string(i) + " ] Could Not Be Initialized", __FILE__, __LINE__); return false; }

		timeUI[i]->setModelMatrix(
			MMath::translate(Vec3(currentOffset, -3.7f, 0.f)) * // Iterates on offset to make sure health icons are spaced apart
			MMath::scale(Vec3(0.1f, 0.2f, 1.0)) * // Identical scales for each
			MMath::rotate(180, Vec3(0.0f, 0.0f, 1.0f))); // face the camera

		currentOffset += timeBarOffset;
	}
#pragma endregion

#pragma region Score
	
	// Score UI Initialization
	const float scoreBarOffset = 0.3f;
	currentOffset = 0.0f;

	for (int i = 0; i < 10; i++) {
		scoreUI[i] = new UIObject(UI_meshPtr, UI_shaderPtr, timeUI_texturePtr[0]);

		if (scoreUI[i] == nullptr) { Debug::FatalError("Score UI [ " + std::to_string(i) + " ] Could Not Be Initialized", __FILE__, __LINE__); return false; }

		scoreUI[i]->setModelMatrix(
			MMath::translate(Vec3(currentOffset, 3.7f, 0.f)) * // Iterates on offset to make sure health icons are spaced apart
			MMath::scale(Vec3(0.1f, 0.2f, 1.0)) * // Identical scales for each
			MMath::rotate(180, Vec3(0.0f, 0.0f, 1.0f))); // face the camera

		currentOffset += scoreBarOffset;
	}
#pragma endregion

#pragma endregion

#pragma region Entities

#pragma region Level
	// Load Level Base Texture
	level_Base_texturePtr = new Texture();
	level_Roof_texturePtr = new Texture();
	if (level_Base_texturePtr->LoadImage("textures/Level_Base.png") == false) { Debug::FatalError("Couldn't Load Level Base Texture", __FILE__, __LINE__); return false; }
	if (level_Roof_texturePtr->LoadImage("textures/Level_Roof.png") == false) { Debug::FatalError("Couldn't Load Level Roof Texture", __FILE__, __LINE__); return false; }


	level_Base = new UIObject(UI_meshPtr, UI_shaderPtr, level_Base_texturePtr);
	level_Roof = new UIObject(UI_meshPtr, UI_shaderPtr, level_Roof_texturePtr);
	if (level_Base == nullptr) { Debug::FatalError("Level Base Could Not Be Initialized", __FILE__, __LINE__); return false; }
	if (level_Roof == nullptr) { Debug::FatalError("Level Roof Could Not Be Initialized", __FILE__, __LINE__); return false; }

	float levelScale = 3.0f;
	level_Base->setModelMatrix(MMath::scale(Vec3(levelScale, levelScale, 1.0)) * MMath::rotate(180, Vec3(0.0f, 0.0f, 1.0f)));
	level_Roof->setModelMatrix(MMath::scale(Vec3(levelScale, levelScale, 1.0)) * MMath::rotate(180, Vec3(0.0f, 0.0f, 1.0f)));
#pragma endregion

#pragma region Ball
	// Load PinBall Texture
	ball_texturePtr = new Texture();
	if (ball_texturePtr->LoadImage("textures/Ball.png") == false) { Debug::FatalError("Couldn't Load PinBall Texture", __FILE__, __LINE__); return false; }
	
	ball = new PinBall(UI_meshPtr, UI_shaderPtr, ball_texturePtr, 0.1f, 0.1f, Vec2(2.5f, 2.5f));
	if (ball == nullptr) { Debug::FatalError("PinBall Could Not Be Initialized", __FILE__, __LINE__); return false; }

	ball->setPos(spawnLocation);
#pragma endregion

#pragma region Paddles
	// Load Paddle Texture
	paddle_texturePtr = new Texture();
	if (paddle_texturePtr->LoadImage("textures/Paddle.png") == false) { Debug::FatalError("Couldn't Load Paddle Texture", __FILE__, __LINE__); return false; }

	paddle_Left = new Paddle(UI_meshPtr, UI_shaderPtr, paddle_texturePtr, Vec2(1.5f,0.5f), Vec3(-1.5f,-1.5f,0.0f), 45.0f, Vec2(1.1f, 0.5f));
	paddle_Right = new Paddle(UI_meshPtr, UI_shaderPtr, paddle_texturePtr, Vec2(1.5f,0.5f), Vec3(1.5f,-1.5f,0.0f), -45.0f, Vec2(1.1f, 0.5f));
	if (paddle_Left == nullptr) { Debug::FatalError("Left Paddle Could Not Be Initialized", __FILE__, __LINE__); return false; }
	if (paddle_Right == nullptr) { Debug::FatalError("Right Paddle Could Not Be Initialized", __FILE__, __LINE__); return false; }

#pragma endregion

#pragma region Affectors
	// Load PinBall Texture
	affector_Default_texturePtr = new Texture();
	affector_Hit_texturePtr = new Texture();
	if (affector_Default_texturePtr->LoadImage("textures/Affector_Default.png") == false) { Debug::FatalError("Couldn't Load Default Affector Texture", __FILE__, __LINE__); return false; }
	if (affector_Hit_texturePtr->LoadImage("textures/Affector_Hit.png") == false) { Debug::FatalError("Couldn't Load Hit Affector Texture", __FILE__, __LINE__); return false; }

  Vec3 affectorPos[5] = { 
		Vec3(1.0f, 0.0f, 0.0f),
		Vec3(1.0f, 1.0f, 0.0f),
		Vec3(0.0f, 1.5f, 0.0f),
		Vec3(-1.0f, 0.0f, 0.0f),
		Vec3(-1.0f, 1.0f, 0.0f),
	};

	for (int i = 0; i < 5; i++) {
		affector[i] = new Affector(UI_meshPtr, UI_shaderPtr, affector_Default_texturePtr, affector_Hit_texturePtr, affectorPos[i], 0.2f, 0.2f, 10);
		if (affector[i] == nullptr) { Debug::FatalError("Affector Could Not Be Initialized", __FILE__, __LINE__); return false; }
	}
#pragma endregion

#pragma region Goals
	goal_WinState_texturePtr = new Texture();
	goal_Deactivated_texturePtr = new Texture();
	goal_LoseState_texturePtr__TEMP = new Texture();
	if (goal_WinState_texturePtr->LoadImage("textures/Goal_Win.png") == false) { Debug::FatalError("Couldn't Load Win Goal Texture", __FILE__, __LINE__); return false; }
	if (goal_Deactivated_texturePtr->LoadImage("textures/Goal_Empty.png") == false) { Debug::FatalError("Couldn't Load Deactivated Goal Texture", __FILE__, __LINE__); return false; }
	if (goal_LoseState_texturePtr__TEMP->LoadImage("textures/Goal_Fail.png") == false) { Debug::FatalError("Couldn't Load Lose Goal Texture", __FILE__, __LINE__); return false; }

	goal_Win = new Goal(UI_meshPtr, UI_shaderPtr, goal_WinState_texturePtr, goal_Deactivated_texturePtr, Vec3(), 0.2f, 0.2f, false);
	goal_Lose = new Goal(UI_meshPtr, UI_shaderPtr, goal_LoseState_texturePtr__TEMP, goal_Deactivated_texturePtr, Vec3(0.0f,-3.0f,0.0f), 0.5f, 0.5f, true);
	if (goal_Win == nullptr) { Debug::FatalError("Win State Goal Could Not Be Initialized", __FILE__, __LINE__); return false; }
	if (goal_Lose == nullptr) { Debug::FatalError("Lose State Could Not Be Initialized", __FILE__, __LINE__); return false; }
#pragma endregion

#pragma endregion

#pragma region Garbage Collection

#pragma endregion

	return true;
}

void TestLevel::Update(const float deltaTime) {
	if (menuState == 0) { // If A Menu Is Open, The Game Is Paused (No Entity Updates)
#pragma region Collision Calculations
		ball->CalculateCollisions();
		paddle_Left->CalculateCollision(ball);
		paddle_Right->CalculateCollision(ball);
		for (int i = 0; i < 5; i++) { score += affector[i]->CalculateCollision(ball); }
		if (goal_Lose->CalculateCollision(ball)) { UpdateHealth(-1); }
		if (goal_Win->CalculateCollision(ball) &&  score >= winScore) { menuState = 2; }
#pragma endregion

#pragma region Entity Update
		if (score >= winScore && !goal_Win->activated) { goal_Win->setActivated(true); }
		ball->Update(deltaTime);
		paddle_Left->Update(deltaTime);
		paddle_Right->Update(deltaTime);
		for (int i = 0; i < 5; i++) { affector[i]->Update(deltaTime); }
		UpdateTime(deltaTime);
		UpdateScore();
#pragma endregion
	}
}

void TestLevel::UpdateHealth(int diff) {
	ball->setPos(spawnLocation);
	ball->setVel(Vec3());

	health = (health + diff > maxHealth) ? maxHealth : health + diff; // cap health to max
	
	// Game State Check (Health). Open Game Over Menu
	if (health <= 0) { menuState = 3; }
}

void TestLevel::UpdateTime(const float deltaTime) {
#pragma region Time Texture Sequence Asign
	int sec = ((int)round(timeremaining) % 60);
	int min = (((int)round(timeremaining) - sec) / 60);
	int x = 0; int y = 0; int z = 0; int w = 0;

	if (min < 10) { y = min; } else { x = (min - (min % 10)) / 10; y = (min % 10); }
	if (sec < 10) { w = sec; } else { z = (sec - (sec % 10)) / 10; w = (sec % 10); }

	int t[5] = { x, y, 10, z, w };

	for (int i = 0; i < 5; i++) {
		int j = t[i];
		timeUI[i]->setTexture(timeUI_texturePtr[j]);
	}
#pragma endregion

	timeremaining -= deltaTime;

	// Game State Check (Time). Open Game Over Menu
	if (timeremaining <= 0.0f) { menuState = 3; }

}

void TestLevel::UpdateScore() {
	std::string scoreChars = std::to_string(score);
	int scorelength = scoreChars.length();
	//std::cout << score << "--------" << scorelength << "---------" << scoreChars.at(0) << std::endl;

	for (int i = 0; i < 10; i++) {
		if (i < scorelength) {
			const char atI = scoreChars.at(i);
			scoreUI[i]->setTexture(timeUI_texturePtr[atoi(&atI)]);
		} else {
			scoreUI[i]->setTexture(timeUI_texturePtr[11]);
		}
	}
}

void TestLevel::HandleEvents(const SDL_Event& sdlEvent) {
#pragma region Debug
	SDL_Event event = sdlEvent;
	if (SDL_PollEvent(&event) == 1) {
		/*if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.keysym.scancode == SDL_SCANCODE_E) { menuState = 1; }
		if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.keysym.scancode == SDL_SCANCODE_W) { menuState = 2; }
		if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.keysym.scancode == SDL_SCANCODE_L) { menuState = 3; }
		if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.keysym.scancode == SDL_SCANCODE_EQUALS) { UpdateHealth(1); }
		if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.keysym.scancode == SDL_SCANCODE_MINUS) { UpdateHealth(-1); }*/
	}
#pragma endregion

#pragma region Begin Play
	if (menuState == 4 && (sdlEvent.key.keysym.scancode == SDL_SCANCODE_SPACE)) {
		menuState = 0;
		ball->setPos(spawnLocation);
		// Activate Starting Ball
	}
#pragma endregion

#pragma region Menus
	// If ((The Esc Key is Pushed) && The No Menu Is Open)? Open Esc Menu : Otherwise (If Esc Menu Is Open)? Close Esc Menu : Otherwise Leave Current Menu Open (This Way, You Don't close The Win/Lose Menu)     
	menuState = (sdlEvent.key.keysym.scancode == SDL_SCANCODE_ESCAPE) ? (menuState == 0) ? 1 : (menuState == 1) ? 0 : menuState : menuState;
	/*if (sdlEvent.key.keysym.scancode == SDL_SCANCODE_ESCAPE) { // Acomplishes the same thing as above
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
			if (StoP.x <= Pause_button_Resume_bounds.x && StoP.y <= Pause_button_Resume_bounds.y && StoP.x >= Pause_button_Resume_bounds.z && StoP.y >= Pause_button_Resume_bounds.w) { buttonPressed = 1; } 
			else if (StoP.x <= Pause_button_Replay_bounds.x && StoP.y <= Pause_button_Replay_bounds.y && StoP.x >= Pause_button_Replay_bounds.z && StoP.y >= Pause_button_Replay_bounds.w) { buttonPressed = 2; } 
			else if (StoP.x <= Pause_button_QuitToMenu_bounds.x && StoP.y <= Pause_button_QuitToMenu_bounds.y && StoP.x >= Pause_button_QuitToMenu_bounds.z && StoP.y >= Pause_button_QuitToMenu_bounds.w) { buttonPressed = 3; } 
			else if (StoP.x <= Pause_button_QuitToDesktop_bounds.x && StoP.y <= Pause_button_QuitToDesktop_bounds.y && StoP.x >= Pause_button_QuitToDesktop_bounds.z && StoP.y >= Pause_button_QuitToDesktop_bounds.w) { buttonPressed = 4; }
			break;
		case 2:
			if (StoP.x <= Win_button_Replay_bounds.x && StoP.y <= Win_button_Replay_bounds.y && StoP.x >= Win_button_Replay_bounds.z && StoP.y >= Win_button_Replay_bounds.w) { buttonPressed = 2; } 
			else if (StoP.x <= Win_button_QuitToMenu_bounds.x && StoP.y <= Win_button_QuitToMenu_bounds.y && StoP.x >= Win_button_QuitToMenu_bounds.z && StoP.y >= Win_button_QuitToMenu_bounds.w) { buttonPressed = 3; } 
			else if (StoP.x <= Win_button_QuitToDesktop_bounds.x && StoP.y <= Win_button_QuitToDesktop_bounds.y && StoP.x >= Win_button_QuitToDesktop_bounds.z && StoP.y >= Win_button_QuitToDesktop_bounds.w) { buttonPressed = 4; }
			break;
		case 3:
			if (StoP.x <= Lose_button_Replay_bounds.x && StoP.y <= Lose_button_Replay_bounds.y && StoP.x >= Lose_button_Replay_bounds.z && StoP.y >= Lose_button_Replay_bounds.w) { buttonPressed = 2; } 
			else if (StoP.x <= Lose_button_QuitToMenu_bounds.x && StoP.y <= Lose_button_QuitToMenu_bounds.y && StoP.x >= Lose_button_QuitToMenu_bounds.z && StoP.y >= Lose_button_QuitToMenu_bounds.w) { buttonPressed = 3; } 
			else if (StoP.x <= Lose_button_QuitToDesktop_bounds.x && StoP.y <= Lose_button_QuitToDesktop_bounds.y && StoP.x >= Lose_button_QuitToDesktop_bounds.z && StoP.y >= Lose_button_QuitToDesktop_bounds.w) { buttonPressed = 4; }
			break;
		}

		std::cout << buttonPressed;
		// Change Current Call Designation To Have The Scene Manager Change Scene
		// See Line 67 In SceneManager
		switch (buttonPressed) {
		case 1:
			menuState = 0;
			break;
		case 2:
			callDesignation = myDesignation;
			break;

		case 3:
			callDesignation = 0;
			break;
		case 4:
			callDesignation = -1;
			break;
		}
	}
#pragma endregion

#pragma region Paddle
	if (menuState == 0) { // If The Game Is Not Paused
		if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.keysym.scancode == SDL_SCANCODE_LEFT) {
			paddle_Left->extended = true;
		} 
		if (sdlEvent.type == SDL_KEYDOWN && sdlEvent.key.keysym.scancode == SDL_SCANCODE_RIGHT) {
			paddle_Right->extended = true;
		}
	}
#pragma endregion
}

void TestLevel::Render() const {
	glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);


#pragma region UI Render
	GLuint Program_Menu = menuUI_Pause->getShader()->getProgram();
	glUseProgram(Program_Menu);

	glUniformMatrix4fv(menuUI_Pause->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
	glUniformMatrix4fv(menuUI_Pause->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix());
	glUniform3fv(menuUI_Pause->getShader()->getUniformID("lightPos"), 1, lightSource_UI);
	// Render Opened Menu, If Any
	switch (menuState) {
	case 0:
		RenderEntities();

		// [] [] [] :: ::  <- health = 3/5
		for (int i = 0; i < health; i++) { healthUI[i]->Render(); }
		for (int i = 0; i < 5; i++) { timeUI[i]->Render(); }
		for (int i = 0; i < 10; i++) { scoreUI[i]->Render(); }
		gameplayUI->Render();
		break;
	case 1:
		menuUI_Pause->Render();
		break;
	case 2:
		menuUI_Win->Render();
		break;
	case 3:
		menuUI_Lose->Render();
		break;
	case 4:
		beginPlayUI->Render();
		gameplayUI->Render();
		break;
	}
#pragma endregion

	glUseProgram(0);
}

void TestLevel::RenderEntities() const {
	GLuint Program_Entity = ball->getShader()->getProgram();
	glUseProgram(Program_Entity);

	glUniformMatrix4fv(ball->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
	glUniformMatrix4fv(ball->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix());
	glUniform3fv(ball->getShader()->getUniformID("lightPos"), 1, lightSource_UI);

	level_Roof->Render();

	ball->Render();
	paddle_Left->Render();
	paddle_Right->Render();
	for (int i = 0; i < 5; i++) {
		affector[i]->Render();
	}
	goal_Win->Render();
	//goal_Lose->Render();

	level_Base->Render();
}

void TestLevel::OnDestroy() {
	//if (meshPtr) delete meshPtr, meshPtr = nullptr;
}
