#ifndef COLLSIONTESTLEVEL_H
#define COLLSIONTESTLEVEL_H
#include "Scene.h"
#include "PinBall.h"

/// <Notes>
/// 
/// </summary>
class CollisionTestLevel : public Scene {
private:
	const static int maxBalls = 10;
	int currentSpawnIndex = 0;
	PinBall* balls[maxBalls];
	GameObject* floor;

public:
	explicit CollisionTestLevel();
	virtual ~CollisionTestLevel();

	virtual bool OnCreate() override;
	virtual void OnDestroy() override;
	virtual void Update(const float deltaTime) override;
	virtual void Render() const override;
	virtual void HandleEvents(const SDL_Event& sdlEvent) override;
};


#endif 