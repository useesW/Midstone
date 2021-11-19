#include "PinBall.h"
#include <iostream>
#include "MMath.h"

PinBall::PinBall(std::string name_, GameObject* parent_, float collisionRadius_, 
					TransformComponent* transform_, RenderComponent* renderer_,
					float mass_, Vec3 gravity_, bool useGravity_, bool isStatic_, Mesh* collisionMesh_) {
	name = name_;
	parent = parent_;
	collisionRadius = collisionRadius_;

	transform = transform_;
	renderer = renderer_;

	mass = mass_;
	pos = transform->position;
	gravity = (isStatic_)? Vec3() : gravity_;
	useGravity = (isStatic_) ? false : useGravity_;
	isStatic = isStatic_;
	collisionMesh = collisionMesh_;
	UpdateModelMatrix();
}

PinBall::PinBall(std::string name_, float collisionRadius_,
					TransformComponent* transform_, RenderComponent* renderer_,
					float mass_, Vec3 gravity_, bool useGravity_, bool isStatic_, Mesh* collisionMesh_) {
	name = name_;
	parent = nullptr;
	collisionRadius = collisionRadius_;

	transform = transform_;
	renderer = renderer_;

	mass = mass_;
	pos = transform->position;
	gravity = (isStatic_) ? Vec3() : gravity_;
	useGravity = (isStatic_) ? false : useGravity_;
	isStatic = isStatic_;
	collisionMesh = collisionMesh_;
	UpdateModelMatrix();
}

PinBall::~PinBall() {}

bool PinBall::OnCreate() { return true; } 
void PinBall::OnDestroy() {}

/// [ Override Unessessary ]--> This method may have to be deleted if the only thing it does is call the gameobjects Update 
//void PinBall::Update(float deltaTime_) {
//	Update(deltaTime_); // GameObject -> Update();
//}

void PinBall::HandleEvents(const SDL_Event& sdlEvent) {}


void PinBall::CalculateCollisions(GameObject* others[]) {
	for (int i = 0; i <= sizeof(others); i++) {
		if (transform->position == others[i]->getPosition()) { 
			continue; 
		} // Skip Self Collision Calculation

		// Limit Collision Calls To Objects Within Radius
		if (RespondCollision(others[i]->getCollisionMesh(), transform->modelMatrix, others[i]->getModelMatrix())) {
			HandleEffects(others[i]->getName());
		}
		/*else if(sqrt(pow(transform->position.x - others[i]->getPosition().x,2) + pow(transform->position.y - others[i]->getPosition().y, 2)) < collisionRadius) { 
			if (RespondCollision(others[i]->getCollisionMesh(), transform->modelMatrix, others[i]->getModelMatrix())) { 
				HandleEffects(others[i]->getName());
			}
		}*/
	}
}

void PinBall::HandleEffects(std::string otherName) {
	/// If the ball collides with a win state goal, the player wins -> let scene know to change menu states
	/// the the player collides with a lose state goal, the player looses one health
	/// 
	/// if the player collides with an affector, -> type of affector -> enable the effect with duration
}




