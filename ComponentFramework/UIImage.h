#ifndef UIImage_H
#define UIImage_H
#include <glew.h>
#include "UIObject.h"

class UIImage: public UIObject {
public:
	UIImage(std::string name_, UIObject* parent, Scene* currentScene_, bool startRendered_,
				TransformComponent* transform_, RenderComponent* renderer_);
	UIImage(std::string name_, Scene* currentScene_, bool startRendered_,
				TransformComponent* transform_, RenderComponent* renderer_);
	UIImage();
	~UIImage();

	bool OnCreate() override;
	void OnDestroy() override;
	void Update(const float deltaTime_) override;
	void HandleEvents(const SDL_Event& sdlEvent) override;

	void setIsRendered(bool isRendered_) { render = isRendered_; }
	void setEnabled(bool enabled_) { enabled = enabled_; }
};
#endif