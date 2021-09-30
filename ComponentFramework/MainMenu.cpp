#include <glew.h>
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

MainMenu::MainMenu() : camera(nullptr), titlemeshPtr(nullptr), buttonmeshPtr(nullptr), titletexturePtr(nullptr), button1texturePtr(nullptr), UIshaderPtr(nullptr) {
	camera = new Camera;
	Debug::Info("Created MainMenu: ", __FILE__, __LINE__);
}

MainMenu::~MainMenu() {}

bool MainMenu::OnCreate() {

	lightSource = Vec3(0.0f, 0.0f, 0.0f);

	return true;
}

void MainMenu::HandleEvents(const SDL_Event& sdlEvent) {

}

void MainMenu::Update(const float deltaTime) {

}

void MainMenu::Render() const {
	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	/// Draw your scene here

	
	glUseProgram(0);
}


void MainMenu::OnDestroy() {
	//if (meshPtr) delete meshPtr, meshPtr = nullptr;
}
