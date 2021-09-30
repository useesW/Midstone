#include <glew.h>
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

TestLevel::TestLevel() : camera(nullptr) {
	camera = new Camera;
	Debug::Info("Created MainMenu: ", __FILE__, __LINE__);
}

TestLevel::~TestLevel() {}

bool TestLevel::OnCreate() {

	lightSource = Vec3(0.0f, 0.0f, 0.0f);

	return true;
}

void TestLevel::HandleEvents(const SDL_Event& sdlEvent) {

}

void TestLevel::Update(const float deltaTime) {

}

void TestLevel::Render() const {
	/// Clear the screen
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	/// Draw your scene here


	glUseProgram(0);
}


void TestLevel::OnDestroy() {
	//if (meshPtr) delete meshPtr, meshPtr = nullptr;
}
