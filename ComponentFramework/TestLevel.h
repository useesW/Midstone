#ifndef TESTLEVEL_H
#define TESTLEVEL_H
#include "Scene.h"
#include "Vector.h"
#include "Matrix.h"
using namespace MATH;

/// Forward declarations 
union SDL_Event;
class Camera;
class UIObject;
class PinBall;
//class Paddle
//class ...
class Mesh;
class Shader;
class Texture;

// Use this for the first stage of dev so we can get the gameplay tested & working
class TestLevel : public Scene {
private:
	const static int maxHealth = 5;
	int myDesignation = 1;

	Camera* camera;
	Vec3 lightSource_UI;

	// States
	/* 0 = No Menu 
	*  1 = Esc Menu
	*  2 = Win Menu
	*  3 = Lose Menu
	*  4 = Begin Play
	*/
	int menuState = 4; // Always Starts With Begin Play Menu Active
	int health = maxHealth;
	int score = 0;
	float timeremaining = 300.00;


	#pragma region UI
	UIObject* menuUI_Esc;
	UIObject* menuUI_Win;
	UIObject* menuUI_Lose;
	UIObject* beginPlayUI;
	UIObject* healthUI[maxHealth]; // When health is removed or added, disable/enable rendering
	UIObject* timeUI[4];

	// UI Shader
	Shader* UI_shaderPtr;

	// UI Mesh
	Mesh* menu_Esc_meshPtr;
	Mesh* menu_Win_meshPtr;
	Mesh* menu_Lose_meshPtr;
	Mesh* beginPlayUI_meshPtr;
	Mesh* healthUI_meshPtr;
	Mesh* timeUI_meshPtr;

	// Texture
	Texture* menu_Esc_texturePtr;
	Texture* menu_Win_texturePtr;
	Texture* menu_Lose_texturePtr;
	Texture* beginPlayUI_texturePtr;
	Texture* healthUI_texturePtr;
	Texture* timeUI_texturePtr[10];

	// Button Bounds
	//Esc
	Vec4 Esc_button_Resume_bounds;
	Vec4 Esc_button_Replay_bounds;
	Vec4 Esc_button_QuitToMenu_bounds;
	Vec4 Esc_button_QuitToDesktop_bounds;

	//Win
	Vec4 Win_button_Replay_bounds;
	Vec4 Win_button_QuitToMenu_bounds;
	Vec4 Win_button_QuitToDesktop_bounds;

	//Lose
	Vec4 Lose_button_Replay_bounds;
	Vec4 Lose_button_QuitToMenu_bounds;
	Vec4 Lose_button_QuitToDesktop_bounds;

	/*
	      Pause Menu                          Win                            Lose

	|     Resume       |             |                  |             |                  |
	|     Replay       |             |     Replay       |             |     Replay       | 
	|     QuitToM      |             |     QuitToM      |             |     QuitToM      |
	|     QuitToD      |             |     QuitToD      |             |     QuitToD      |
	*/

	#pragma endregion


	#pragma region Entities
	// This array will be deleted and reinitialized after every health change (adding or subrtacting a ball).
	PinBall* balls[maxHealth];
	Mesh* ball_meshPtr;
	Texture* ball_texturePtr;



	// The remaining entities are persistant
	// Paddles* paddles[x];
	// Affector* affectors[y];
	// Goal* goals[z];

	// May just have to hard-code length
	Vec3 lightsources[1]; // fill with entitity positions (which emit light)
	Vec4 lightcolors[1]; // fill with entitity light colors
	#pragma endregion



public:
	explicit TestLevel();
	virtual ~TestLevel();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event& sdlEvent) override;

	// Gameplay Methods
	void UpdateHealth(int diff);
	void UpdateTime(const float deltaTime);
	void PauseUnpause(int gameState, int _menuState); // gameState (whether to pause or unpause)
};


#endif 