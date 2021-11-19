#ifndef SCENE_H
#define SCENE_H
#include "Vector.h"
#include "Matrix.h"
#include "MMath.h"
#include "Camera.h"

using namespace MATH;
union SDL_Event;

class Scene {
public:
	int mydesignation = -100;
	int callDesignation = -100;
	/* Designations
	* -100 = Do Nothing
	* -1   = Quit
	*  0   = Main Menu
	*  1   = This Level (Replay) 
	*  x   = Level x (Exclude Current)
	*/
	int menuState = 0;
	// States
	/* 0 = No Menu
	*  1 = Main/Pause Menu
	*  2 = Win Menu
	*  3 = Lose Menu
	*  4 = Begin Play
	*  5 = Credits Menu
	*/

	float screenWidth;
	float screenHeight;

	Camera* camera;
	Vec3 lightSource_UI;
	Vec3 lightSource_Ambient;

	explicit Scene() {}
	virtual ~Scene() {}

	virtual bool OnCreate() = 0;
	virtual void OnDestroy() = 0;
	virtual void Update(const float deltaTime) = 0;
	virtual void Render() const  = 0 ;
	virtual void HandleEvents(const SDL_Event &sdlEvent) = 0;
	virtual void ForceDesignation(int designation_) { callDesignation = designation_; }
	virtual void ForceMenuState(int state_) { menuState = state_; }

	inline Vec2 getScreenSize() { Vec2 rVec = Vec2(); rVec.x = screenWidth; rVec.y = screenHeight; return rVec; }
	inline Matrix4 getCameraProjectionMatrix() { return camera->getProjectionMatrix(); }
	inline Matrix4 getCameraViewMatrix() { return camera->getViewMatrix(); }
	
};
#endif