#ifndef UIBUTTON_H
#define UIBUTTON_H
#include <glew.h>
#include "UIObject.h"

class UIButton : public UIObject {
public:
	Vec4 clickBounds;

	UIButton(std::string name_, UIObject* parent, Scene* currentScene_, bool startEnebled_, Vec4 clickBounds_,
				TransformComponent* transform_, RenderComponent* renderer_);
	UIButton(std::string name_, Scene* currentScene_, bool startEnebled_, Vec4 clickBounds_,
				TransformComponent* transform_, RenderComponent* renderer_);
	UIButton();
	~UIButton();

	bool OnCreate() override;
	void OnDestroy() override;
	void Update(const float deltaTime_) override;
	void HandleEvents(const SDL_Event& sdlEvent) override;
	
	void setIsRendered(bool isRendered_) { render = isRendered_; }
	void setEnabled(bool enabled_) { enabled = enabled_; }
};

#endif