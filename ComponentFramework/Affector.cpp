#include "Affector.h"
#include <iostream>
#include "MMath.h"

Affector::Affector() {
	
}

Affector::~Affector() {}

bool Affector::OnCreate() { return true; }
void Affector::OnDestroy() {}

/// [ Override Unessessary ]--> This method may have to be deleted if the only thing it does is call the gameobjects Update 
void Affector::Update(float deltaTime_) {
	Update(deltaTime_); // GameObject -> Update();
}

void Affector::HandleEvents(const SDL_Event& sdlEvent) {}
