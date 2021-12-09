#ifndef AFFECTOR_H
#define AFFECTOR_H
#include <glew.h>
#include "Matrix.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "GameObject.h"

/*To-Do (Pseudo-Code)
* Different Effects
* Generally This Class Would Hold The: Name & Durration of the effect which the ball would use (Name = "SpeedMultiply" --> Ball INcreases Speed for duration)
* Right Now, we only have the speed effect, so you can just make this class spefically for that instead of making it dynamic for all other effects
*/

// completed paddles 
using namespace MATH;

class Affector : public GameObject {
public:

	Affector();
	~Affector();

	bool OnCreate() override;
	void OnDestroy() override;
	void Update(const float deltaTime_) override;
	void HandleEvents(const SDL_Event& sdlEvent) override;
};

#endif