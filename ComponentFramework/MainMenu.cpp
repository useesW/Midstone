#include "MainMenu.h"
#include <glew.h>
#include <SDL.h>
#include <iostream>
#include "Debug.h"
#include "ObjLoader.h"

#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

#include "UIPanel.h"
#include "UIButton.h"
#include "UIImage.h"


MainMenu::MainMenu() {
	camera = new Camera;
	mydesignation = 0;
	menuState = 1;
	lightSource_UI = Vec3(0.0f, 0.0f, 0.0f);
	lightSource_Ambient = Vec3(0.0f, 0.0f, 0.0f);
	Debug::Info("Created Main Menu: ", __FILE__, __LINE__);
}

MainMenu::~MainMenu() {}

bool MainMenu::OnCreate() {
	std::string name_ = "";

#pragma region UI Panel Initialization
	Shader* PTR_Shader_Menu = new Shader("shaders/texturePhongVert.glsl", "shaders/texturePhongFrag.glsl");
	if (PTR_Shader_Menu  == nullptr) { Debug::FatalError("Couldn't create UI Shader", __FILE__, __LINE__); return false; } // Shader Initialization Check
	if (ObjLoader::loadOBJ("meshes/UI_Mesh.obj") == false) { Debug::FatalError("Couldn't load background object", __FILE__, __LINE__); return false; }
	Mesh* PTR_Mesh_Menu = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);

#pragma region Main Menu
	Texture* PTR_Texture_Panel_Main = new Texture();
	if (PTR_Texture_Panel_Main->LoadImage("textures/Menu_Main.png") == false) { Debug::FatalError("Couldn't load background texture", __FILE__, __LINE__); return false; }

	name_ = "Main_Menu";
	TransformComponent* transform_Main = new TransformComponent(Vec3(0.0f, 0.0f, 0.0f), Vec3(7.4f,4.15f,1.0f), 0.0f, Matrix4());
	RenderComponent* renderer_Main = new RenderComponent(PTR_Mesh_Menu, PTR_Texture_Panel_Main, PTR_Shader_Menu);

	panel_Menu_Main = new UIPanel(name_, true, this, transform_Main, renderer_Main);
	if (panel_Menu_Main == nullptr) { Debug::FatalError("Background could not be initialized", __FILE__, __LINE__); return false; }
#pragma endregion

#pragma region Credits Menu
	Texture* PTR_Texture_Panel_Credits = new Texture();
	if (PTR_Texture_Panel_Credits->LoadImage("textures/Menu_Credits.png") == false) { Debug::FatalError("Couldn't load Credit texture", __FILE__, __LINE__); return false; }

	name_ = "Credit_Menu";
	TransformComponent* transform_Credits = new TransformComponent(Vec3(0.0f, 0.0f, 0.0f), Vec3(7.4f, 4.15f, 1.0f), 0.0f, Matrix4());
	RenderComponent* renderer_Credits = new RenderComponent(PTR_Mesh_Menu, PTR_Texture_Panel_Credits, PTR_Shader_Menu);

	panel_Menu_Credits = new UIPanel(name_, false, this, transform_Credits, renderer_Credits); 
	if (panel_Menu_Credits == nullptr) { Debug::FatalError("Credits could not be initialized", __FILE__, __LINE__); return false; }
#pragma endregion

#pragma endregion

#pragma region Buttons
	int arrayLegnth_ = 4;

#pragma region Main Menu Buttons
	Texture* PTR_Texture_Button_Play = new Texture();
	Texture* PTR_Texture_Button_Quit = new Texture();
	Texture* PTR_Texture_Button_Credits = new Texture();
	if (PTR_Texture_Button_Play->LoadImage("textures/Button_Play.png") == false) { Debug::FatalError("Couldn't load background texture", __FILE__, __LINE__); return false; }
	if (PTR_Texture_Button_Quit->LoadImage("textures/Button_Quit.png") == false) { Debug::FatalError("Couldn't load background texture", __FILE__, __LINE__); return false; }
	if (PTR_Texture_Button_Credits->LoadImage("textures/Button_Credits.png") == false) { Debug::FatalError("Couldn't load background texture", __FILE__, __LINE__); return false; }


	arrayLegnth_ = 3;
	std::string names_Main[3] = { "Play","QuitToDesktop", "Credits"};
	// Click Bounds Direction -> Vec4( TopR +x ,  TopR +y ,  BotL -x ,   BotL -y )
	Vec4 clickBounds_Main[3] = {
		Vec4(710, 279, 568, 199),
		Vec4(710, 399, 569, 319),
		Vec4(710, 520,569, 440)	};
	TransformComponent* transforms_Main[3] = {
		new TransformComponent(Vec3(0.0f, 0.3f, 1.0f), Vec3(0.1f,0.1f,0.1f), 0.0f, Matrix4()),
		new TransformComponent(Vec3(0.0f, 0.0f, 1.0f), Vec3(0.1f,0.1f,0.1f), 0.0f, Matrix4()),
		new TransformComponent(Vec3(0.0f, -0.3f, 1.0f), Vec3(0.15f,0.1f,0.1f), 0.0f, Matrix4())	};
	RenderComponent* renderers_Main[3] = {
		new RenderComponent(PTR_Mesh_Menu, PTR_Texture_Button_Play, PTR_Shader_Menu),
		new RenderComponent(PTR_Mesh_Menu, PTR_Texture_Button_Quit, PTR_Shader_Menu),
		new RenderComponent(PTR_Mesh_Menu, PTR_Texture_Button_Credits, PTR_Shader_Menu)	};

	panel_Menu_Main->CreateButtons(arrayLegnth_, names_Main, clickBounds_Main, transforms_Main, renderers_Main);
#pragma endregion

#pragma region Credit Menu Buttons
	Texture* PTR_Texture_Button_ExitCredits = new Texture();
	if (PTR_Texture_Button_ExitCredits->LoadImage("textures/Button_QuitToMenu.png") == false) { Debug::FatalError("Couldn't load background texture", __FILE__, __LINE__); return false; }

	arrayLegnth_ = 1;
	std::string names_Credits[1] = { "ExitCredits"};
	// Click Bounds Direction -> Vec4( TopR +x ,  TopR +y ,  BotL -x ,   BotL -y )
	Vec4 clickBounds_Credits[1] = { Vec4(1280, 720, 0, 0) };
	TransformComponent* transforms_Credits[1] = { new TransformComponent(Vec3(0.0f, 0.0f, 0.0f), Vec3(0.1f,0.1f,0.1f), 0.0f, Matrix4()) };
	RenderComponent* renderers_Credits[1] = { new RenderComponent(PTR_Mesh_Menu, PTR_Texture_Button_Credits, PTR_Shader_Menu) };

	panel_Menu_Credits->CreateButtons(arrayLegnth_, names_Credits, clickBounds_Credits, transforms_Credits, renderers_Credits);
#pragma endregion


#pragma endregion


	return true;
}

void MainMenu::Update(const float deltaTime) {
	switch (menuState) {
	case 1:
		if (!panel_Menu_Main->getIsRendered()) { panel_Menu_Main->setIsRendered(true); }
		if (panel_Menu_Credits->getIsRendered()) { panel_Menu_Credits->setIsRendered(false); }
		break;
	case 5:
		if (!panel_Menu_Credits->getIsRendered()) { panel_Menu_Credits->setIsRendered(true); }
		if (panel_Menu_Main->getIsRendered()) { panel_Menu_Main->setIsRendered(false); }
		break;
	}
}

void MainMenu::HandleEvents(const SDL_Event& sdlEvent) {
	if (sdlEvent.type == SDL_EventType::SDL_MOUSEBUTTONDOWN) {
		//Vec2 mouseCoords = Vec2(); mouseCoords.x = sdlEvent.button.x; mouseCoords.y = sdlEvent.button.y;
		//std::cout << "Mouse Coords vec2( " << mouseCoords.x << ", " << mouseCoords.y << ") \n";

		panel_Menu_Main->HandleEvents(sdlEvent);
		panel_Menu_Credits->HandleEvents(sdlEvent);
	}

	
}

void MainMenu::Render() const {
	glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	GLuint ProgramMenu = panel_Menu_Main->getShader()->getProgram();

	glUseProgram(ProgramMenu);

	glUniformMatrix4fv(panel_Menu_Main->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
	glUniformMatrix4fv(panel_Menu_Main->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix());
	glUniform3fv(panel_Menu_Main->getShader()->getUniformID("lightPos"), 1, lightSource_UI);

	panel_Menu_Main->Render();
	panel_Menu_Credits->Render();

	glUseProgram(0);
}

// Comented Lines May Become Obsolete
void MainMenu::OnDestroy() {
	// Object Cleanup
	//if (camera) delete camera, camera = nullptr;
	//if (backbround) delete backbround, backbround = nullptr;
	//if (creditMenu) delete creditMenu, creditMenu = nullptr;

	//if (playButton) delete playButton, playButton = nullptr;
	//if (quitButton) delete quitButton, quitButton = nullptr;
	//if (creditButton) delete creditButton, creditButton = nullptr;

	// Shader Cleanup
	//if (UI_shaderPtr) delete UI_shaderPtr, UI_shaderPtr = nullptr;

	// Mesh Cleanup
	//if (background_meshPtr) delete background_meshPtr, background_meshPtr = nullptr;
	//if (credit_meshPtr) delete credit_meshPtr, credit_meshPtr = nullptr;
	//if (button_meshPtr) delete button_meshPtr, button_meshPtr  = nullptr;

	// Texture Cleanup
	//if (background_texturePtr) delete background_texturePtr, background_texturePtr = nullptr;
	//if (credit_texturePtr) delete credit_texturePtr, credit_texturePtr = nullptr;
	//if (button_Play_texturePtr) delete button_Play_texturePtr, button_Play_texturePtr = nullptr;
	//if (button_Quit_texturePtr) delete button_Quit_texturePtr, button_Quit_texturePtr = nullptr;
	//if (button_Credit_texturePtr) delete button_Credit_texturePtr, button_Credit_texturePtr = nullptr;
}

