#ifndef PINBALL_H
#define PINBALL_H
#include <glew.h>
#include "Matrix.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "GameObject.h"
#include "PhysicsObject.h"
//#include "Paddle.h"

using namespace MATH;

// Once the module objects are created using this model, delete it
class PinBall : public PhysicsObject, public GameObject {

private:
	Matrix4 modelMatrix;
	Mesh* mesh;
	Shader* shader;
	Texture* texture;
	Vec2 gameboundsTemp;
	float radius;
	
public:
	PinBall(Mesh* mesh_, Shader* shader_, Texture* texture_);
	~PinBall();
	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void Update(const float deltaTime_);
	virtual void Render() const;
	virtual void HandleEvents(const SDL_Event& event);


	inline Shader* getShader() const { return shader; }
	inline void setModelMatrix(const Matrix4& modelMatrix_) { modelMatrix = modelMatrix_; }
	inline const Matrix4& getModelMatrix() { return modelMatrix; }
	void CalculateCollisions(PinBall* balls[]);
	inline Vec2 LineIntersection(Vec2 s1, Vec2 e1, Vec2 s2, Vec2 e2);
};

#endif

