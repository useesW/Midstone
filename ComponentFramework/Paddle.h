#ifndef PADDLE_H
#define PADDLE_H
#include <glew.h>
#include "GameObject.h"

/*To-Do (Pseudo-Code)
* Input Events (Paddle Rotate)
*/
using namespace MATH;

class Paddle : public GameObject {
public:

	Paddle(std::string name_, GameObject* parent_, float collisionRadius_,
			TransformComponent* transform_, RenderComponent* renderer_,
			float mass_, Vec3 gravity_, bool useGravity_, bool isStatic_, Mesh* collisionMesh_);
	Paddle(std::string name_, float collisionRadius_,
			TransformComponent* transform_, RenderComponent* renderer_,
			float mass_, Vec3 gravity_, bool useGravity_, bool isStatic_, Mesh* collisionMesh_);
	~Paddle();

	bool OnCreate() override;
	void OnDestroy() override;
	void Update(const float deltaTime_) override;
	void HandleEvents(const SDL_Event& sdlEvent) override;
};

#endif