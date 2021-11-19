#include "CollisionTestLevel.h"
#include <glew.h>
#include <SDL.h>
#include <iostream>
#include "Debug.h"
#include "ObjLoader.h"

#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"

CollisionTestLevel::CollisionTestLevel() {
	camera = new Camera;
	mydesignation = 0;
	menuState = 1;
	lightSource_UI = Vec3(0.0f, 0.0f, 0.0f);
	lightSource_Ambient = Vec3(0.0f, 0.0f, 0.0f);
	Debug::Info("Created Main Menu: ", __FILE__, __LINE__);
}

CollisionTestLevel::~CollisionTestLevel() {}

bool CollisionTestLevel::OnCreate() {
	Shader* PTR_Shader = new Shader("shaders/texturePhongVert.glsl", "shaders/texturePhongFrag.glsl");
	if (PTR_Shader == nullptr) { Debug::FatalError("Couldn't create UI Shader", __FILE__, __LINE__); return false; } // Shader Initialization Check

	if (ObjLoader::loadOBJ("meshes/UI_Mesh.obj") == false) { Debug::FatalError("Couldn't load background object", __FILE__, __LINE__); return false; }
	Mesh* PTR_Render_Mesh = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);
	Mesh* PTR_Collision_Mesh_Floor = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);


	if (ObjLoader::loadOBJ("meshes/UI_Mesh.obj") == false) { Debug::FatalError("Couldn't load background object", __FILE__, __LINE__); return false; }
	Mesh* PTR_Collision_Mesh_Ball = new Mesh(GL_TRIANGLES, ObjLoader::vertices, ObjLoader::normals, ObjLoader::uvCoords);


	Texture* PTR_Texture_Ball = new Texture();
	if (PTR_Texture_Ball->LoadImage("textures/ball.png") == false) { Debug::FatalError("Couldn't load background texture", __FILE__, __LINE__); return false; }


	for (int i = 0; i < maxBalls; i++) {
		balls[i] = new PinBall("ball" + std::to_string(i), 1.0f, 
								new TransformComponent(Vec3(0.0f, 0.0f, 30.0f), Vec3(0.3f, 0.3f, 0.1f), 45.0f, Matrix4()), 
								new RenderComponent(PTR_Render_Mesh, PTR_Texture_Ball, PTR_Shader),
								1.0f, Vec3(0.0f,-9.8f,0.0f) , false, false, PTR_Collision_Mesh_Ball);
	}

	Texture* PTR_Texture_Floor= new Texture();
	if (PTR_Texture_Floor->LoadImage("textures/Menu_Credits.png") == false) { Debug::FatalError("Couldn't load background texture", __FILE__, __LINE__); return false; }
	floor = new GameObject("floor", new TransformComponent(Vec3(0.0f, -5.0f, 0.0f), Vec3(7.4f, 2.0f, 1.0f), 0.0f, Matrix4()),
							new RenderComponent(PTR_Render_Mesh, PTR_Texture_Floor, PTR_Shader),
							1.0f, Vec3(0.0f, 0.0f, 0.0f), false, true, PTR_Collision_Mesh_Floor);
	return true;
}

void CollisionTestLevel::Update(const float deltaTime) {
	GameObject* objects[maxBalls + 1];
	objects[0] = floor;
	for (int i = 1; i < maxBalls + 1; i++) {
		objects[i] = balls[i];
	}

	for (int i = 0; i < maxBalls; i++) {
		balls[i]->CalculateCollisions(objects);
		balls[i]->Update(deltaTime);
	}
}

void CollisionTestLevel::HandleEvents(const SDL_Event& sdlEvent) {
	if (sdlEvent.type == SDL_EventType::SDL_MOUSEBUTTONDOWN) {
		Vec2 mouseCoords = Vec2(); mouseCoords.x = sdlEvent.button.x; mouseCoords.y = sdlEvent.button.y;
		Vec3 StoP = MMath::viewToWorldCoord(mouseCoords, screenWidth, screenHeight, camera->getProjectionMatrix(), camera->getViewMatrix());
		StoP.z = 0;
		//std::cout << "Mouse Coords vec2( " << StoP.x << ", " << StoP.y << ", " << StoP.z << ") \n";

		balls[currentSpawnIndex]->setPosition(StoP * 10);
		balls[currentSpawnIndex]->UpdateModelMatrix();
		balls[currentSpawnIndex]->setUseGravity(true);
		balls[currentSpawnIndex]->setVel(Vec3());

		currentSpawnIndex++;
		if (currentSpawnIndex == maxBalls) {
			currentSpawnIndex = 0;
		}
	}


}

void CollisionTestLevel::Render() const {
	glClearColor(0.0f, 1.0f, 0.0f, 0.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);

	GLuint ProgramMenu = balls[0]->getShader()->getProgram();

	glUseProgram(ProgramMenu);

	glUniformMatrix4fv(balls[0]->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, camera->getProjectionMatrix());
	glUniformMatrix4fv(balls[0]->getShader()->getUniformID("viewMatrix"), 1, GL_FALSE, camera->getViewMatrix());
	glUniform3fv(balls[0]->getShader()->getUniformID("lightPos"), 1, lightSource_UI);

	for (int i = 0; i < maxBalls; i++) {
		balls[i]->Render();
	}

	floor->Render();

	glUseProgram(0);
}

// Comented Lines May Become Obsolete
void CollisionTestLevel::OnDestroy() {}

