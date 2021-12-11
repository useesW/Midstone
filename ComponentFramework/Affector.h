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
using namespace MATH;
class PinBall;

class Affector : public GameObject {
public:
	int scoreIteration;
	float collisionRadius;
	Vec3 pos;
	bool hit;
	float hitDurration_Set = 0.2f;
	float hitDurration_Current;

	Matrix4 modelMatrix;
	Mesh* mesh;
	Shader* shader;
	Texture* default_Texture;
	Texture* hit_Texture;
	float textureScale;

	Affector(Mesh* mesh_, Shader* shader_, Texture* default_Texture_, Texture* hit_Texture_, Vec3 pos_, float textureScale_, float collisionRadius_, int scoreIteration_);
	~Affector();

	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void Update(const float deltaTime_);
	virtual void HandleEvents(const SDL_Event& event);
	virtual void Render() const;

	int CalculateCollision(PinBall* ball);
};

#endif