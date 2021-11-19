#ifndef UIPANEL_H
#define UIPANEL_H
#include <glew.h>
#include "UIButton.h"
#include "UIImage.h"
#include "UIObject.h"


class UIPanel: public UIObject {
public:
	int buttonArraylegnth;
	int imageArraylegnth;
	UIButton buttons[10];
	UIImage images[30];

	UIPanel(std::string name_, UIObject* parent, bool startEnebled_, Scene* currentScene_,
				TransformComponent* transform_, RenderComponent* renderer_);
	UIPanel(std::string name_, bool startEnebled_, Scene* currentScene_,
				TransformComponent* transform_, RenderComponent* renderer_);
	UIPanel() {};
	~UIPanel();

	bool OnCreate() override;
	void OnDestroy() override;
	void Update(const float deltaTime_) override;
	void HandleEvents(const SDL_Event& sdlEvent) override;
	void Render() const override;

	void CreateButtons(int arrayLegnth, std::string names[], Vec4 clickBounds[], TransformComponent* transforms[], RenderComponent* renderers[]);
	void CreateImages(int arrayLegnth, std::string names[], TransformComponent* transforms[], RenderComponent* renderers[]);
	void EnableImageGroup(std::string imageNameSignifier, std::string imageNameReferences[], int referenceArrayLegnth);
	void setIsRendered(bool isRendered_);
	void setEnabled(bool enabled_);

	

};

#endif