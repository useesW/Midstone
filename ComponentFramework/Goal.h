#ifndef GOAL_H
#define GOAL_H
#include <glew.h>
#include "GameObject.h"

/*To-Do (Pseudo-Code)
* Probably the simplest of the three, this one just lets the ball know wheather its a win state or lose state so that, when the ball collides with it, the ball will let the level know what to do
*/
using namespace MATH;

class Goal : public GameObject {
public:

	Goal(std::string name_, GameObject* parent_, float collisionRadius_,
			TransformComponent* transform_, RenderComponent* renderer_,
			float mass_, Vec3 gravity_, bool useGravity_, bool isStatic_, Mesh* collisionMesh_);
	Goal(std::string name_, float collisionRadius_,
			TransformComponent* transform_, RenderComponent* renderer_,
			float mass_, Vec3 gravity_, bool useGravity_, bool isStatic_, Mesh* collisionMesh_);
	~Goal();

	bool OnCreate() override;
	void OnDestroy() override;
	void Update(const float deltaTime_) override;
	void HandleEvents(const SDL_Event& sdlEvent) override;
};

#endif
