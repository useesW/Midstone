#ifndef MAINMENU_H
#define MAINMENU_H
#include "Scene.h"
#include "Vector.h"
#include "Matrix.h"
using namespace MATH;

/// Forward declarations 
union SDL_Event;
class Camera;
//class UIObject
class Mesh;
class Shader;
class Texture;

class MainMenu : public Scene {
private:

	Camera* camera;
	Vec3 lightSource;

	#pragma region UI
	// UIobject backbround;
	// UIobject title;
	// UIobject levelButton1;
	// UIobject levelButton...;

	// UI Mesh
	Mesh* titlemeshPtr;
	Mesh* buttonmeshPtr;

	// Texture
	Texture* titletexturePtr;
	Texture* button1texturePtr;
	//Texture* buttonxtexturePtr;

	// UI Shader
	Shader* UIshaderPtr;
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