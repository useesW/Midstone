#include "Camera.h"
#include "MMath.h"
#include "Mesh.h"
#include "Shader.h"
#include "SkyBox.h"
#include "Trackball.h"

Camera::Camera(): skybox(nullptr) {
	projectionMatrix = MMath::perspective(45.0f, (16.0f / 9.0f), 0.5f, 100.0f);
	viewMatrix = MMath::lookAt(Vec3(0.0f, 0.0f, 10.0f), Vec3(0.0f, 0.0f, 0.0f), Vec3(0.0f, 1.0f, 0.0f));
	skybox = new SkyBox();
	trackBall = new Trackball;
}

Camera::~Camera() {
	delete skybox;
	delete trackBall;
}
bool Camera::OnCreate() { return true; }
void Camera::OnDestroy() {}
void Camera::Update(const float deltaTime){}
void Camera::HandleEvents(const SDL_Event& sdlEvent) {
	trackBall->HandleEvents(sdlEvent);
	//skybox->HandleEvents(sdlEvent); // Just In Case
}
void Camera::Render() const{
	glUseProgram(skybox->getShader()->getProgram());
	glUniformMatrix4fv(skybox->getShader()->getUniformID("projectionMatrix"), 1, GL_FALSE, projectionMatrix);
	glUniformMatrix4fv(skybox->getShader()->getUniformID("cameraRotationMatrix"), 1, GL_FALSE, trackBall->getMatrix4());
	skybox->Render();
	glUseProgram(0);
}
