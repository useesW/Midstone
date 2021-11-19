#include "UIButton.h"
#include "MMath.h"
#include <SDL.h>

UIButton::UIButton(std::string name_, UIObject* parent_, Scene* currentScene_, bool startRendered_, Vec4 clickBounds_,
					TransformComponent* transform_, RenderComponent* renderer_) {
	name = name_;
	parent = parent_;
	currentScene = currentScene_;
	render = startRendered_;
	enabled = true;

	clickBounds = clickBounds_;

	transform = transform_;
	renderer = renderer_;
	UpdateModelMatrix();
}

UIButton::UIButton(std::string name_, Scene* currentScene_, bool startRendered_, Vec4 clickBounds_,
					TransformComponent* transform_, RenderComponent* renderer_) {
	name = name_;
	parent = nullptr;
	currentScene = currentScene_;
	render = startRendered_;
	enabled = true;

	clickBounds = clickBounds_;

	transform = transform_;
	renderer = renderer_;
	UpdateModelMatrix();
}

UIButton::UIButton() {}
UIButton::~UIButton() {}

bool UIButton::OnCreate() { return true; }
void UIButton::OnDestroy() {}
void UIButton::Update(const float deltaTime_) {}
void UIButton::HandleEvents(const SDL_Event& sdlEvent) {
	if (render && sdlEvent.type == SDL_EventType::SDL_MOUSEBUTTONDOWN) {

		Vec2 mouseCoords = Vec2(); mouseCoords.x = sdlEvent.button.x; mouseCoords.y = sdlEvent.button.y;
		if (mouseCoords.x <= clickBounds.x && 
			mouseCoords.y <= clickBounds.y && 
			mouseCoords.x >= clickBounds.z && 
			mouseCoords.y >= clickBounds.w) {
			std::cout << "Click " << name << std::endl;

			if (name == "Credits") { currentScene->ForceMenuState(5); }
			if (name == "Play") { currentScene->ForceDesignation(1); }
			if (name == "QuitToDesktop") { currentScene->ForceDesignation(-1); }
			if (name == "QuitToMenu") { currentScene->ForceDesignation(0); }
			if (name == "Replay") { currentScene->ForceDesignation(currentScene->mydesignation); }
			if (name == "Resume") { currentScene->ForceMenuState(0); }
			if (name == "ExitCredits") { currentScene->ForceMenuState(1); }
		}
	}
}
