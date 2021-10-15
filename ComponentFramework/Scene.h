#ifndef SCENE_H
#define SCENE_H
union SDL_Event;
class Scene {
public:
	int callDesignation;
	/* -100 = Do Nothing
	* -1 = Quit
	*  0 = Main Menu
	*  +x = Level x
	*/

	float screenWidth;
	float screenHeight;

	explicit Scene() {}
	virtual ~Scene() {}

	virtual bool OnCreate() = 0;
	virtual void OnDestroy() = 0;
	virtual void Update(const float deltaTime) = 0;
	virtual void Render() const  = 0 ;
	virtual void HandleEvents(const SDL_Event &sdlEvent) = 0;

protected:
	
};
#endif