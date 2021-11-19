#include "UIPanel.h"

UIPanel::UIPanel(std::string name_, UIObject* parent_, bool startRendered_, Scene* currentScene_,
					TransformComponent* transform_, RenderComponent* renderer_) {
	name = name_;
	parent = parent_;
	render = startRendered_;
	enabled = true;
	currentScene = currentScene_;

	transform = transform_;
	renderer = renderer_;
	UpdateModelMatrix();
}

UIPanel::UIPanel(std::string name_, bool startRendered_, Scene* currentScene_,
					TransformComponent* transform_, RenderComponent* renderer_) {
	buttonArraylegnth = imageArraylegnth = 0;
	name = name_;
	parent = nullptr;
	render = startRendered_;
	enabled = true;
	currentScene = currentScene_;

	transform = transform_;
	renderer = renderer_;
	UpdateModelMatrix();
}

UIPanel::~UIPanel() {}

bool UIPanel::OnCreate() { return true; }
void UIPanel::OnDestroy() {}
void UIPanel::Update(const float deltaTime_) {}
void UIPanel::HandleEvents(const SDL_Event& sdlEvent) {
	if (!render) { return; }
	for (int i = 0; i < buttonArraylegnth; i++) {
		buttons[i].HandleEvents(sdlEvent);
	}
	for (int i = 0; i < imageArraylegnth; i++) {
		images[i].HandleEvents(sdlEvent);
	}
}

void UIPanel::Render() const {
	if (!render) { return; }
	UIObject::Render();
	for (int i = 0; i < buttonArraylegnth; i++) {
		buttons[i].Render();
	}
	for (int i = 0; i < imageArraylegnth; i++) {
		images[i].Render();
	}
}

void UIPanel::CreateButtons(int arrayLegnth, std::string names[], Vec4 clickBounds[], TransformComponent* transforms[], RenderComponent* renderers[]) {
	for (int i = buttonArraylegnth; i < buttonArraylegnth + arrayLegnth; i++) {
		buttons[i] = UIButton(names[i],this,currentScene,render, clickBounds[i],transforms[i],renderers[i]);
	}
	buttonArraylegnth += arrayLegnth;
}

void UIPanel::CreateImages(int arrayLegnth, std::string names[], TransformComponent* transforms[], RenderComponent* renderers[]) {
	std::cout << imageArraylegnth << std::endl;
	std::cout << imageArraylegnth + arrayLegnth << std::endl;
	for (int i = imageArraylegnth; i < imageArraylegnth + arrayLegnth; i++) {
		images[i] = UIImage(names[i], this, currentScene, render, transforms[i], renderers[i]);
	}
	imageArraylegnth = arrayLegnth;
	std::cout << "Images Created" << std::endl;
}

void UIPanel::EnableImageGroup(std::string imageNameSignifier, std::string imageNameReferences[], int referenceArrayLegnth) {
	for (int i = 0; i < imageArraylegnth; i++) {
		if (images[i].getName().find(imageNameSignifier) != std::string::npos) {
			images[i].setEnabled(false);
			for (int j = 0; j < referenceArrayLegnth; j++) {
				if (images[i].getName() == imageNameReferences[j]) { 
					images[i].setEnabled(true); 
					std::cout << "aaaaaaaaaaaaaaaaaaaa" << std::endl;
				}
			}
		}
	}
}

void UIPanel::setIsRendered(bool isRendered_) {
	render = isRendered_;
	for (int i = 0; i < buttonArraylegnth; i++) { buttons[i].setIsRendered(isRendered_); }
	for (int i = 0; i < imageArraylegnth; i++) { images[i].setIsRendered(isRendered_); }
}

void UIPanel::setEnabled(bool enabled_) {
	enabled = enabled_;
	for (int i = 0; i < buttonArraylegnth; i++) { buttons[i].setEnabled(enabled_); }
	for (int i = 0; i < imageArraylegnth; i++) { images[i].setEnabled(enabled_); }
}