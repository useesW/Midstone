#ifndef PADDLE_H
#define PADDLE_H
#include <glew.h>
#include "Matrix.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "GameObject.h"

/*To-Do (Pseudo-Code)
* Input Events (Paddle Rotate)
*/
using namespace MATH;

class Paddle : public GameObject {
public:

	Paddle();
	~Paddle();

	bool OnCreate() override;
	void OnDestroy() override;
	void Update(const float deltaTime_) override;
	void HandleEvents(const SDL_Event& sdlEvent) override;
};

#endif