#ifndef TESTLEVEL_H
#define TESTLEVEL_H
#include "Scene.h"
#include "PinBall.h"
#include "Paddle.h"
#include "Affector.h"
#include "Goal.h"

//class Pinball;
//class Paddle;
//class Affector;
//class Goal;
class UIPanel;
class UIButton;
class UIImage;

/// <Notes>
/// 
/// </summary>
class TestLevel : public Scene {
private:
	
	const static int winScore = 100;
	const static int maxHealth = 5;

	int score = 0;
	int health = maxHealth;
	float timeremaining = 300.00;

	UIPanel* panel_Gameplay;
	UIPanel* panel_Menu_BeginPlay;
	UIPanel* panel_Menu_Pause;
	UIPanel* panel_Menu_Win;
	UIPanel* panel_Menu_Lose;

	Texture* PTRs_Textures_Time[10];

	PinBall* balls[maxHealth];
	Paddle* paddles[4];
	Affector* affectors[10];
	Goal* goals[2];

	Vec3 lightsources_Entites[1]; // fill with entitity positions (which emit light)
	Vec4 lightcolors_Entites[1]; // fill with entitity light colors



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