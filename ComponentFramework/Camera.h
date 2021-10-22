#ifndef CAMERA_H
#define CAMERA_H
#include "GameObject.h"
#include "Matrix.h"
#include "Trackball.h"

class SkyBox;

using namespace MATH;

class Camera :public GameObject {
private:
	Matrix4 projectionMatrix;
	Matrix4 viewMatrix;
	SkyBox *skybox;
	Trackball *trackBall;
	

public:
	Camera();
	~Camera();
	
	bool OnCreate() override;
	void OnDestroy() override;
	void Update(const float deltaTime) override;
	void HandleEvents(const SDL_Event& sdlEvent) override;
	void Render() const;

	Matrix4 getProjectionMatrix() { return projectionMatrix; }
	Matrix4 getViewMatrix() { return viewMatrix; }
	Matrix4 getCameraRotationMatrix() { return trackBall->getMatrix4(); }
	SkyBox* getSkyBox() { return skybox; };
	//test 
	
};

#endif