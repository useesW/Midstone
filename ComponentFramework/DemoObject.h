#ifndef OBJECT_H
#define OBJECT_H
#include <glew.h>
#include "Matrix.h"
#include "Mesh.h"
#include "Shader.h"
#include "Texture.h"
#include "GameObject.h"
#include "PhysicsObject.h"

using namespace MATH;

// Once the module objects are created using this model, delete it
class DemoObject: public PhysicsObject, public GameObject {	

private:
	Matrix4 modelMatrix;
	Mesh *mesh;
	Shader *shader;
	Texture *texture;
	DemoObject *parent;
public:
	DemoObject(Mesh *mesh_, Shader *shader_, Texture *texture_);
	DemoObject(DemoObject *parent_, Mesh *mesh_, Shader *shader_, Texture *texture_);
	~DemoObject();
	virtual bool OnCreate();
	virtual void OnDestroy();
	virtual void Update(const float deltaTime_);
	virtual void Render() const;
	virtual void HandleEvents(const SDL_Event &event);


	inline Shader* getShader() const { return shader; }
	inline void setModelMatrix(const Matrix4 &modelMatrix_) { modelMatrix = modelMatrix_; }
	inline const Matrix4& getModelMatrix() { return modelMatrix; }
};

#endif

