#ifndef TESTLEVEL_H
#define TESTLEVEL_H
#include "Scene.h"
#include "Vector.h"
#include "Matrix.h"

using namespace MATH;

union SDL_Event;
class Camera;
class UIObject;
class PinBall;
class Paddle;
class Affector;
class Goal;

class Mesh;
class Shader;
class Texture;

// Use this for the first stage of dev so we can get the gameplay tested & working
class TestLevel : public Scene {
private:
	int myDesignation = 1;
	// States
	/* 0 = No Menu
	*  1 = Esc Menu
	*  2 = Win Menu
	*  3 = Lose Menu
	*  4 = Begin Play
	*/
	int menuState = 4; // Always Starts With Begin Play Menu Active
	bool bulletTime = false;

	Camera* camera;
	Vec3 lightSource_UI;

	const static int maxHealth = 5;
	const static int winScore = 10;
	int health = maxHealth;
	int score = 0;
	float timeremaining = 300.00;
	Vec3 spawnLocation = Vec3(-1.65f, 3.0f, 0.0f);

#pragma region UI
	UIObject* menuUI_Pause;
	UIObject* menuUI_Win;
	UIObject* menuUI_Lose;
	UIObject* beginPlayUI;
	UIObject* gameplayUI;

	UIObject* scoreUI[12];
	UIObject* healthUI[maxHealth];
	UIObject* timeUI[5];

	// UI Shader
	Shader* UI_shaderPtr;
	Mesh* UI_meshPtr;

	// Texture
	Texture* menu_Pause_texturePtr;
	Texture* menu_Win_texturePtr;
	Texture* menu_Lose_texturePtr;
	Texture* beginPlayUI_texturePtr;
	Texture* gameplayUI_texturePtr;

	Texture* scoreUI_texturePtr[9];
	Texture* healthUI_texturePtr;
	Texture* timeUI_texturePtr[10];

#pragma region Button Bounds
	//Pause
	Vec4 Pause_button_Resume_bounds;
	Vec4 Pause_button_Replay_bounds;
	Vec4 Pause_button_QuitToMenu_bounds;
	Vec4 Pause_button_QuitToDesktop_bounds;

	//Win
	Vec4 Win_button_Replay_bounds;
	Vec4 Win_button_QuitToMenu_bounds;
	Vec4 Win_button_QuitToDesktop_bounds;

	//Lose
	Vec4 Lose_button_Replay_bounds;
	Vec4 Lose_button_QuitToMenu_bounds;
	Vec4 Lose_button_QuitToDesktop_bounds;

	/*   Pause Menu                         Win                             Lose
	|     Resume       |             |                  |             |                  |
	|     Replay       |             |     Replay       |             |     Replay       |
	|     QuitToM      |             |     QuitToM      |             |     QuitToM      |
	|     QuitToD      |             |     QuitToD      |             |     QuitToD      |
	*/
#pragma endregion

#pragma endregion


#pragma region Entities
	UIObject* level_Base;
	UIObject* level_Roof;
	Texture* level_Base_texturePtr;
	Texture* level_Roof_texturePtr;


	PinBall* ball;
	Texture* ball_texturePtr;

	Paddle* paddle_Left;
	Paddle* paddle_Right;
	Texture* paddle_texturePtr;

	Affector* affector[5];
	Texture* affector_Default_texturePtr;
	Texture* affector_Hit_texturePtr;

	// Goal* goals[z];
	Goal* goal_Win;
	Goal* goal_Lose;
	Texture* goal_WinState_texturePtr;
	Texture* goal_Deactivated_texturePtr;
	Texture* goal_LoseState_texturePtr__TEMP;

#pragma endregion



public:
	explicit TestLevel();
	virtual ~TestLevel();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void HandleEvents(const SDL_Event& sdlEvent) override;
	virtual void Render() const override;


	// Gameplay Methods
	void UpdateHealth(int diff);
	void UpdateTime(const float deltaTime);
	void UpdateScore();
	void RenderEntities() const;
};


#endif 