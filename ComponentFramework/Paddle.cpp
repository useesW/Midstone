#include "Paddle.h"
#include <iostream>
#include "MMath.h"

Paddle::Paddle(std::string name_, GameObject* parent_, float collisionRadius_,
				TransformComponent* transform_, RenderComponent* renderer_,
				float mass_, Vec3 gravity_, bool useGravity_, bool isStatic_, Mesh* collisionMesh_) {
	name = name_;
	parent = parent_;

	transform = transform_;
	renderer = renderer_;

	mass = mass_;
	gravity = (isStatic_) ? Vec3() : gravity_;
	useGravity = (isStatic_) ? false : useGravity_;
	isStatic = isStatic_;
	collisionMesh = collisionMesh_;
}

Paddle::Paddle(std::string name_, float collisionRadius_,
				TransformComponent* transform_, RenderComponent* renderer_,
				float mass_, Vec3 gravity_, bool useGravity_, bool isStatic_, Mesh* collisionMesh_) {
	name = name_;
	parent = nullptr;

	transform = transform_;
	renderer = renderer_;

	mass = mass_;
	gravity = (isStatic_) ? Vec3() : gravity_;
	useGravity = (isStatic_) ? false : useGravity_;
	isStatic = isStatic_;
	collisionMesh = collisionMesh_;
}

Paddle::~Paddle() {}

bool Paddle::OnCreate() { return true; }
void Paddle::OnDestroy() {}

/// [ Override Unessessary ]--> This method may have to be deleted if the only thing it does is call the gameobjects Update 
void Paddle::Update(float deltaTime_) {
	Update(deltaTime_); // GameObject -> Update();
}

void Paddle::HandleEvents(const SDL_Event& sdlEvent) {}
