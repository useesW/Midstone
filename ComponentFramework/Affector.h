#ifndef AFFECTOR_H
#define AFFECTOR_H
#include <glew.h>
#include "GameObject.h"

/*To-Do (Pseudo-Code)
* Different Effects
* Generally This Class Would Hold The: Name & Durration of the effect which the ball would use (Name = "SpeedMultiply" --> Ball INcreases Speed for duration)
* Right Now, we only have the speed effect, so you can just make this class spefically for that instead of making it dynamic for all other effects
*/
using namespace MATH;

class Affector : public GameObject {
public:

	Affector(std::string name_, GameObject* parent_, float collisionRadius_,
				TransformComponent* transform_, RenderComponent* renderer_,
				float mass_, Vec3 gravity_, bool useGravity_, bool isStatic_, Mesh* collisionMesh_);

	Affector(std::string name_, float collisionRadius_,
				TransformComponent* transform_, RenderComponent* renderer_,
				float mass_, Vec3 gravity_, bool useGravity_, bool isStatic_, Mesh* collisionMesh_);
	~Affector();

	bool OnCreate() override;
	void OnDestroy() override;
	void Update(const float deltaTime_) override;
	void HandleEvents(const SDL_Event& sdlEvent) override;
};

#endif