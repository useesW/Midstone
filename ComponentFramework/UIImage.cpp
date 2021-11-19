#include "UIImage.h"

UIImage::UIImage(std::string name_, UIObject* parent_, Scene* currentScene_, bool startRendered_,
					TransformComponent* transform_, RenderComponent* renderer_) {
	name = name_;

	parent = parent_;
	currentScene = currentScene_;
	render = startRendered_;
	enabled = true;

	transform = transform_;
	renderer = renderer_;

	UpdateModelMatrix();

}

UIImage::UIImage(std::string name_, Scene* currentScene_, bool startRendered_,
					TransformComponent* transform_, RenderComponent* renderer_) {
	name = name_;
	parent = nullptr;
	currentScene = currentScene_;
	render = startRendered_;
	enabled = true;

	transform = transform_;
	renderer = renderer_;
	UpdateModelMatrix();
}

UIImage::UIImage() {}
UIImage::~UIImage() {}

bool UIImage::OnCreate() { return true; }
void UIImage::OnDestroy() {}
void UIImage::Update(const float deltaTime_) {}
void UIImage::HandleEvents(const SDL_Event& sdlEvent) {}