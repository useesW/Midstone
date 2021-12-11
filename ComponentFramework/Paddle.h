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
class PinBall;

class Paddle : public GameObject {
public:

	Vec3 pos;
	Vec3 startPos;
	Vec3 extendedPos;
	Vec3 extentionNormal;
	bool extended;
	
	float percentComplete;
	float extentionTime;
	float elapsedTime;

	float rotation;
	Vec2 collisionBounds;

	Matrix4 modelMatrix;
	Mesh* mesh;
	Shader* shader;
	Texture* texture;
	Vec2 textureScale;

	Paddle(Mesh* mesh_, Shader* shader_, Texture* texture_, Vec2 textureScale_, Vec3 pos_, float rotation_, Vec2 collisionBounds_);
	~Paddle();

	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void Update(const float deltaTime_);
	virtual void HandleEvents(const SDL_Event& event);
	virtual void Render() const;

	void CalculateCollision(PinBall* ball);

};

#endif