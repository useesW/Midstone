#ifndef MAINMENU_H
#define MAINMENU_H
#include "Scene.h"
#include "Vector.h"
#include "Matrix.h"
using namespace MATH;

/// Forward declarations 
union SDL_Event;
class Camera;
class UIObject;
class Mesh;
class Shader;
class Texture;

class MainMenu : public Scene {
private:

	Camera* camera;
	Vec3 lightSource;
	bool creditInUse = false;

#pragma region UI
	UIObject* backbround;
	UIObject* creditMenu;

	// UI Shader
	Shader* UI_shaderPtr;
	Mesh* UI_meshPtr;

	// Texture
	Texture* background_texturePtr;
	Texture* credit_texturePtr;

	// Button Bounds
	Vec4 button_Play_bounds;
	Vec4 button_Quit_bounds;
	Vec4 button_Credit_bounds;

#pragma endregion

public:
	explicit MainMenu();
	virtual ~MainMenu();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event& sdlEvent) override;
};


#endif // SCENE0_H