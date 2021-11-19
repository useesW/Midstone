#ifndef PINBALL_H
#define PINBALL_H
#include <glew.h>
#include "GameObject.h"

using namespace MATH;

class PinBall : public GameObject {
public:
	float collisionRadius;

	PinBall(std::string name_, GameObject* parent_, float collisionRadius_,
				TransformComponent* transform_, RenderComponent* renderer_,
				float mass_, Vec3 gravity_, bool useGravity_, bool isStatic_, Mesh* collisionMesh_);
	PinBall(std::string name_, float collisionRadius_,
				TransformComponent* transform_, RenderComponent* renderer_,
				float mass_, Vec3 gravity_, bool useGravity_, bool isStatic_, Mesh* collisionMesh_);
	PinBall() {};
	~PinBall();

	bool OnCreate() override;
	void OnDestroy() override;
	//void Update(const float deltaTime_) override;
	void HandleEvents(const SDL_Event& sdlEvent) override;

	void CalculateCollisions(GameObject* others[]);
	void HandleEffects(std::string otherName);
};

#endif

