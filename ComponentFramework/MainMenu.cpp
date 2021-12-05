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

MainMenu::MainMenu() : camera(nullptr), backbround(nullptr),
UI_shaderPtr(nullptr), UI_meshPtr(nullptr),
background_texturePtr(nullptr), credit_texturePtr(nullptr) {

	camera = new Camera;
	lightSource = Vec3(0.0f, 0.0f, 0.0f);
	Debug::Info("Created MainMenu: ", __FILE__, __LINE__);
}

//Tommy hoang

MainMenu::~MainMenu() {}

bool MainMenu::OnCreate() {
#pragma region UI Initialization
	UI_shaderPtr = new Shader("shaders/texturePhongVert.glsl", "shaders/texturePhongFrag.glsl");
	if (UI_shaderPtr == nullptr) { Debug::FatalError("Couldn't Create UI Shader", __FILE__, __LINE__); return false; } // Shader Initialization Check

	if (ObjLoader::loadOBJ("meshes/UI_Panel.obj") == false) { Debug::FatalError("Couldn't UI Panel Object", __FILE__, __LINE__); return false; }
	UI_meshPtr = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);

	float UIScaleFactor = 0.46f;


#pragma region Background
	// Load Background Texture
	background_texturePtr = new Texture();
	if (background_texturePtr->LoadImage("textures/Menu_Main.png") == false) { Debug::FatalError("Couldn't Load Main Menu Texture", __FILE__, __LINE__); return false; }

	// Background Initialization
	backbround = new UIObject(UI_meshPtr, UI_shaderPtr, background_texturePtr);
	if (backbround == nullptr) { Debug::FatalError("Main Menu Could Not Be Initialized", __FILE__, __LINE__); return false; }

	backbround->setModelMatrix(MMath::scale(Vec3(16.0 * UIScaleFactor, 9.0 * UIScaleFactor, 1.0)) * MMath::rotate(180, Vec3(0.0f, 0.0f, 1.0f)));
#pragma endregion


#pragma region Credits
	// Load Credit Texture
	credit_texturePtr = new Texture();
	if (credit_texturePtr->LoadImage("textures/Default_Background.png") == false) { Debug::FatalError("Couldn't Load Credits Texture", __FILE__, __LINE__); return false; }

	// Credit Initialization
	creditMenu = new UIObject(UI_meshPtr, UI_shaderPtr, credit_texturePtr);
	if (creditMenu == nullptr) { Debug::FatalError("Credits Could Not Be Initialized", __FILE__, __LINE__); return false; }

	creditMenu->setModelMatrix(MMath::scale(Vec3(16.0 * UIScaleFactor, 9.0 * UIScaleFactor, 1.0)) * MMath::rotate(180, Vec3(0.0f, 0.0f, 1.0f)));
#pragma endregion
#pragma endregion


#pragma region Buttons
	// Bounds Direction -> Vec4( TopR +x ,  TopR +y ,  BotL -x ,   BotL -y )
	button_Play_bounds = Vec4(0.1139090, 0.1679870, -0.116210, 0.08054150);
	button_Quit_bounds = Vec4(0.0978004, 0.0264637, -0.103553, -0.0609815);
	button_Credit_bounds = Vec4(0.1852460, -0.124264, -0.170288, -0.2140100);
#pragma endregion


	return true;
}

void MainMenu::HandleEvents(const SDL_Event& sdlEvent) {
	if (sdlEvent.type == SDL_EventType::SDL_MOUSEBUTTONDOWN) {
		if (creditInUse) { // Click anywhere to close Credits
			creditInUse = false;
		} else { // If on Main Menu page
			Vec2 mouseCoords = Vec2(sdlEvent.button.x, sdlEvent.button.y);
			Vec3 StoP = MMath::viewToWorldCoord(mouseCoords, screenWidth, screenHeight, camera->getProjectionMatrix(), camera->getViewMatrix());
			//std::cout << "Mouse Coords vec2( " << mouseCoords.x << ", " << mouseCoords.y << ") |    |" << "World Coords vec3( " << StoP.x << ", " << StoP.y << ", " << StoP.z << " ) \n";

			// Check which button, if any, the cousor is on
			int buttonPressed = 0;
			if (StoP.x <= button_Play_bounds.x && StoP.y <= button_Play_bounds.y && StoP.x >= button_Play_bounds.z && StoP.y >= button_Play_bounds.w) { buttonPressed = 1; } else if (StoP.x <= button_Quit_bounds.x && StoP.y <= button_Quit_bounds.y && StoP.x >= button_Quit_bounds.z && StoP.y >= button_Quit_bounds.w) { buttonPressed = 2; } else if (StoP.x <= button_Credit_bounds.x && StoP.y <= button_Credit_bounds.y && StoP.x >= button_Credit_bounds.z && StoP.y >= button_Credit_bounds.w) { buttonPressed = 3; }

			// change current call dasignation to have the scene manager change scene
			// See line 67 in SceneManager
			switch (buttonPressed) {
			case 1:
				callDesignation = 1;
				break;
			case 2:
				callDesignation = -1;
				break;
			case 3:
				creditInUse = true;
				break;
			}
		}
	}
}

void MainMenu::Update(const float deltaTime) {}

void MainMenu::Render() const {
	glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	GLuint ProgramMenu = backbround->getShader()->getProgram();

	glUseProgram(ProgramMenu);

	glUniformMatrix4fv(backbround->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
	glUniformMatrix4fv(backbround->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix());
	glUniform3fv(backbround->getShader()->getUniformID("lightPos"), 1, lightSource);

	if (!creditInUse) {
		backbround->Render();
	} else { creditMenu->Render(); }

	glUseProgram(0);
}

// Comented Lines May Become Obsolete
void MainMenu::OnDestroy() {
	// Object Cleanup
	if (camera) delete camera, camera = nullptr;
	if (backbround) delete backbround, backbround = nullptr;
	if (creditMenu) delete creditMenu, creditMenu = nullptr;

	// UI Cleanup
	if (UI_shaderPtr) delete UI_shaderPtr, UI_shaderPtr = nullptr;
	if (UI_meshPtr) delete UI_meshPtr, UI_meshPtr = nullptr;

	// Texture Cleanup
	if (background_texturePtr) delete background_texturePtr, background_texturePtr = nullptr;
	if (credit_texturePtr) delete credit_texturePtr, credit_texturePtr = nullptr;
}

