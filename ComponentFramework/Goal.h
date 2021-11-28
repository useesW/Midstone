#ifndef GOAL_H
#define GOAL_H
#include <glew.h>
#include "Matrix.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "GameObject.h"

/*To-Do (Pseudo-Code)
* Probably the simplest of the three, this one just lets the ball know wheather its a win state or lose state so that, when the ball collides with it, the ball will let the level know what to do
*/
using namespace MATH;

class Goal : public GameObject {
public:

	Goal();
	~Goal();

	bool OnCreate() override;
	void OnDestroy() override;
	void Update(const float deltaTime_) override;
	void HandleEvents(const SDL_Event& sdlEvent) override;
};

#endif
