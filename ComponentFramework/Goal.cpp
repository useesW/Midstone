#include "Goal.h"
#include <iostream>
#include "MMath.h"

Goal::Goal() {

}

Goal::~Goal() {}

bool Goal::OnCreate() { return true; }
void Goal::OnDestroy() {}

/// [ Override Unessessary ]--> This method may have to be deleted if the only thing it does is call the gameobjects Update 
void Goal::Update(float deltaTime_) {
	Update(deltaTime_); // GameObject -> Update();
}

void Goal::HandleEvents(const SDL_Event& sdlEvent) {}
