#ifndef TESTLEVEL_H
#define TESTLEVEL_H
#include "Scene.h"
#include "Vector.h"
#include "Matrix.h"
using namespace MATH;

/// Forward declarations 
union SDL_Event;
class Camera;
//class UIObject
//class Pinball
//class Paddle
//class ...
class Mesh;
class Shader;
class Texture;

// Use this for the first stage of dev so we can get the gameplay tested & working
class TestLevel : public Scene {
private:

	Camera* camera;
	Vec3 lightSource;
	bool menuOpen = false;
	float timer;
	int health; // set this to the starting health of the player




public:
	explicit TestLevel();
	virtual ~TestLevel();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event& sdlEvent) override;
};


#endif // SCENE0_H