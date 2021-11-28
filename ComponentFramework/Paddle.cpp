#include "Paddle.h"
#include <iostream>
#include "MMath.h"

Paddle::Paddle() {

}

Paddle::~Paddle() {}

bool Paddle::OnCreate() { return true; }
void Paddle::OnDestroy() {}

/// [ Override Unessessary ]--> This method may have to be deleted if the only thing it does is call the gameobjects Update 
void Paddle::Update(float deltaTime_) {
	Update(deltaTime_); // GameObject -> Update();
}

void Paddle::HandleEvents(const SDL_Event& sdlEvent) {}
