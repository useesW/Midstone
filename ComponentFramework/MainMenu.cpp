#include <glew.h>
#include <SDL.h>
#include <iostream>
#include "Debug.h"
#include "MMath.h"
#include "Physics.h"
#include "ObjLoader.h"
#include "MainMenu.h"
#include "Camera.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "UIObject.h"

MainMenu::MainMenu() : camera(nullptr), backbround(nullptr), UI_shaderPtr(nullptr),
						background_meshPtr(nullptr), credit_meshPtr(nullptr), 
						background_texturePtr(nullptr), credit_texturePtr(nullptr) {
	Debug::Info("Created MainMenu: ", __FILE__, __LINE__);
}

MainMenu::~MainMenu() {}

bool MainMenu::OnCreate() {

	

	camera = new Camera;
	lightSource = Vec3(5.0f, 0.0f, 0.0f);

	#pragma region UI Initialization
	UI_shaderPtr = new Shader("shaders/texturePhongVert.glsl", "shaders/texturePhongFrag.glsl");
	if (UI_shaderPtr == nullptr) { Debug::FatalError("Couldn't create UI Shader", __FILE__, __LINE__); return false; } // Shader Initialization Check
	
	float UIScaleFactor = 0.46f;


	#pragma region Background
	// Load Background Mesh
	if (ObjLoader::loadOBJ("meshes/Menu_Background.obj") == false) { Debug::FatalError("Couldn't load background object", __FILE__, __LINE__); return false; }
	background_meshPtr = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);


	// Load Background Texture
	background_texturePtr = new Texture();
	if (background_texturePtr->LoadImage("textures/MenuPage.png") == false) { Debug::FatalError("Couldn't load background texture", __FILE__, __LINE__); return false; }


	// Asset Pointer Check
	if (background_meshPtr == nullptr || background_texturePtr == nullptr) { Debug::FatalError("Couldn't create Background assets", __FILE__, __LINE__); return false; }


	// Background Initialization
	backbround = new UIObject(background_meshPtr, UI_shaderPtr, background_texturePtr);
	if (backbround == nullptr) { Debug::FatalError("Background could not be initialized", __FILE__, __LINE__); return false; }

	backbround->setModelMatrix(MMath::scale(Vec3(16.0 * UIScaleFactor, 9.0 * UIScaleFactor, 1.0)) * MMath::rotate(180, Vec3(0.0f, 0.0f, 1.0f)));
	#pragma endregion


	#pragma region Credits
	// Load Credit Mesh
	if (ObjLoader::loadOBJ("meshes/Menu_Background.obj") == false) { Debug::FatalError("Couldn't load background object", __FILE__, __LINE__); return false; }
	credit_meshPtr = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);

	// Load Credit Texture
	credit_texturePtr = new Texture();
	if (credit_texturePtr->LoadImage("textures/BackgroundAndTitle.png") == false) { Debug::FatalError("Couldn't load Credit texture", __FILE__, __LINE__); return false; }

	// Credit Initialization
	creditMenu = new UIObject(credit_meshPtr, UI_shaderPtr, credit_texturePtr);
	if (creditMenu == nullptr) { Debug::FatalError("Credits could not be initialized", __FILE__, __LINE__); return false; }

	creditMenu->setModelMatrix(MMath::translate(Vec3(0.0,0.0,-1.0)) * MMath::scale(Vec3(16.0 * UIScaleFactor, 9.0 * UIScaleFactor, 1.0)) * MMath::rotate(180, Vec3(0.0f, 0.0f, 1.0f)));
	#pragma endregion


	#pragma region Buttons
	// Bounds Direction -> Vec4( TopR +x ,  TopR +y ,  BotL -x ,   BotL -y )
	button_Play_bounds   = Vec4(0.1139090, 0.1679870, -0.116210, 0.08054150);
	button_Quit_bounds   = Vec4(0.0978004, 0.0264637, -0.103553, -0.0609815);
	button_Credit_bounds = Vec4(0.1852460, -0.124264, -0.170288, -0.2140100);

	// Obsolete Button Initialization --> No longer using testured objects
	/* 
	// Load Button Mesh
	if (ObjLoader::loadOBJ("meshes/Menu_Button.obj") == false) { Debug::FatalError("Couldn't load button object", __FILE__, __LINE__); return false; }
	button_meshPtr = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);

	#pragma region Play
	// Load Play Button Texture
	button_Play_texturePtr = new Texture();
	if (button_Play_texturePtr->LoadImage("textures/PlayButton.png") == false) { Debug::FatalError("Couldn't load play button texture", __FILE__, __LINE__); return false; }

	// Asset Pointer Check
	if (button_meshPtr == nullptr || button_Play_texturePtr == nullptr) { Debug::FatalError("Couldn't create play button assets", __FILE__, __LINE__); return false; }


	// Play Button Initialization
	playButton = new UIObject(button_meshPtr, UI_shaderPtr, button_Play_texturePtr);
	if (playButton == nullptr) { Debug::FatalError("Play Button could not be initialized", __FILE__, __LINE__); return false; }

	playButton->setModelMatrix(MMath::translate(Vec3(0.0, 1.12, 1.0)) * MMath::scale(Vec3(16.0 * 0.185, 9.0 * 0.29f, 1.0)) * MMath::rotate(180, Vec3(0.0f, 0.0f, 1.0f)));
	#pragma endregion

	#pragma region Quit
	// Load Play Button Texture
	button_Quit_texturePtr = new Texture();
	if (button_Quit_texturePtr->LoadImage("textures/QuitButton.png") == false) { Debug::FatalError("Couldn't load quit button texture", __FILE__, __LINE__); return false; }

	// Asset Pointer Check
	if (button_meshPtr == nullptr || button_Quit_texturePtr == nullptr) { Debug::FatalError("Couldn't create quit button assets", __FILE__, __LINE__); return false; }


	// Play Button Initialization
	quitButton = new UIObject(button_meshPtr, UI_shaderPtr, button_Quit_texturePtr);
	if (quitButton == nullptr) { Debug::FatalError("Quit Button could not be initialized", __FILE__, __LINE__); return false; }

	quitButton->setModelMatrix(MMath::translate(Vec3(-0.025, -0.16, 1.0)) * MMath::scale(Vec3(16.0 * 0.16, 9.0 * 0.29f, 1.0)) * MMath::rotate(180, Vec3(0.0f, 0.0f, 1.0f)));
	#pragma endregion

	#pragma region Credit
	// Load Credit Button Texture
	button_Credit_texturePtr = new Texture();
	if (button_Credit_texturePtr->LoadImage("textures/CreditButton.png") == false) { Debug::FatalError("Couldn't load credit button texture", __FILE__, __LINE__); return false; }

	// Asset Pointer Check
	if (button_meshPtr == nullptr || button_Credit_texturePtr == nullptr) { Debug::FatalError("Couldn't create credit button assets", __FILE__, __LINE__); return false; }


	// Credit Button Initialization
	creditButton = new UIObject(button_meshPtr, UI_shaderPtr, button_Credit_texturePtr);
	if (creditButton == nullptr) { Debug::FatalError("Credit Button could not be initialized", __FILE__, __LINE__); return false; }

	creditButton->setModelMatrix(MMath::translate(Vec3(0.057, -1.52, 1.0)) * MMath::scale(Vec3(16.0 * 0.283, 9.0 * 0.295f, 1.0)) * MMath::rotate(180, Vec3(0.0f, 0.0f, 1.0f)));
	#pragma endregion
	#pragma endregion
	*/
	#pragma endregion


	return true;
}

void MainMenu::HandleEvents(const SDL_Event& sdlEvent) {

	// Mouse Down On Main Page
	if (sdlEvent.type == SDL_EventType::SDL_MOUSEBUTTONDOWN && !creditInUse) {

		Vec2 mouseCoords = Vec2(); mouseCoords.x = sdlEvent.button.x; mouseCoords.y = sdlEvent.button.y;
		Vec3 StoP = MMath::viewToWorldCoord(mouseCoords, screenWidth, screenHeight, camera->getProjectionMatrix(), camera->getViewMatrix());
		//std::cout << "Mouse Coords vec2( " << mouseCoords.x << ", " << mouseCoords.y << ") |    |" << "World Coords vec3( " << StoP.x << ", " << StoP.y << ", " << StoP.z << " ) \n";

		// Check which button, if any, the cousor is on
		int buttonPressed = 0;
		if (StoP.x <= button_Play_bounds.x && StoP.y <= button_Play_bounds.y && StoP.x >= button_Play_bounds.z && StoP.y >= button_Play_bounds.w) { buttonPressed = 1; }
		else if (StoP.x <= button_Quit_bounds.x && StoP.y <= button_Quit_bounds.y && StoP.x >= button_Quit_bounds.z && StoP.y >= button_Quit_bounds.w) { buttonPressed = 2; }
		else if (StoP.x <= button_Credit_bounds.x && StoP.y <= button_Credit_bounds.y && StoP.x >= button_Credit_bounds.z && StoP.y >= button_Credit_bounds.w) { buttonPressed = 3; }

		// change current call dasignation to have the scene manager change scene
		// see line 67 in SceneManager
		switch (buttonPressed) {
		case 0:
			std::cout << "No Button Pressed" << "\n";
			break;

		case 1:
			std::cout << "Play" << "\n";
			callDesignation = 1;
			break;

		case 2:
			std::cout << "Quit" << "\n";
			callDesignation = -1;
			break;

		case 3:
			std::cout << "Open Credit" << "\n";
			creditInUse = true;
			Matrix4 creditMatrix = creditMenu->getModelMatrix() * MMath::translate(Vec3(0.0,0.0,2.0));
			creditMenu->setModelMatrix(creditMatrix);
			break;
		}
	}

	// Mouse Down On Credit Page
	else if (sdlEvent.type == SDL_EventType::SDL_MOUSEBUTTONDOWN && creditInUse) {
		std::cout << "Close Credit" << "\n";
		creditInUse = false;
		Matrix4 creditMatrix = creditMenu->getModelMatrix() * MMath::translate(Vec3(0.0, 0.0, -2.0));
		creditMenu->setModelMatrix(creditMatrix);
	}
}

void MainMenu::Update(const float deltaTime) {
	
}

void MainMenu::Render() const {
	/// Clear the screen
	glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	/// Draw your scene here
	GLuint ProgramMenu = backbround->getShader()->getProgram();

	glUseProgram(ProgramMenu);

	glUniformMatrix4fv(backbround->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
	glUniformMatrix4fv(backbround->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix());
	glUniform3fv(backbround->getShader()->getUniformID("lightPos"), 1, lightSource);

	backbround->Render();
	creditMenu->Render();
	
	glUseProgram(0);
}

// Comented Lines May Become Obsolete
void MainMenu::OnDestroy() {
	// Object Cleanup
	if (camera) delete camera, camera = nullptr;
	if (backbround) delete backbround, backbround = nullptr;
	if (creditMenu) delete creditMenu, creditMenu = nullptr;

	//if (playButton) delete playButton, playButton = nullptr;
	//if (quitButton) delete quitButton, quitButton = nullptr;
	//if (creditButton) delete creditButton, creditButton = nullptr;

	// Shader Cleanup
	if (UI_shaderPtr) delete UI_shaderPtr, UI_shaderPtr = nullptr;

	// Mesh Cleanup
	if (background_meshPtr) delete background_meshPtr, background_meshPtr = nullptr;
	if (credit_meshPtr) delete credit_meshPtr, credit_meshPtr = nullptr;
	//if (button_meshPtr) delete button_meshPtr, button_meshPtr  = nullptr;

	// Texture Cleanup
	if (background_texturePtr) delete background_texturePtr, background_texturePtr = nullptr;
	if (credit_texturePtr) delete credit_texturePtr, credit_texturePtr = nullptr;
	//if (button_Play_texturePtr) delete button_Play_texturePtr, button_Play_texturePtr = nullptr;
	//if (button_Quit_texturePtr) delete button_Quit_texturePtr, button_Quit_texturePtr = nullptr;
	//if (button_Credit_texturePtr) delete button_Credit_texturePtr, button_Credit_texturePtr = nullptr;
}

