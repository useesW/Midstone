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
class PinBall;

class Goal : public GameObject {
public:
	bool activated;
	Vec3 pos;
	float collisionRadius;

	Matrix4 modelMatrix;
	Mesh* mesh;
	Shader* shader;
	Texture* inactive_Texture;
	Texture* active_Texture;
	float textureScale;

	Goal(Mesh* mesh_, Shader* shader_, Texture* active_Texture_, Texture* inactive_Texture_, Vec3 pos_, float textureScale_, float collisionRadius_, bool activated_);
	~Goal();

	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void Update(const float deltaTime_);
	virtual void HandleEvents(const SDL_Event& event);
	virtual void Render() const;

	bool CalculateCollision(PinBall* ball);

	void setActivated(bool state) { activated = state; }
};

#endif
