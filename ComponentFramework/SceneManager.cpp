#include <SDL.h>
#include "SceneManager.h"
#include "Timer.h"
#include "Window.h"
#include "MainMenu.h"
#include "TestLevel.h"



SceneManager::SceneManager(): 
	currentScene(nullptr), window(nullptr), timer(nullptr),
	fps(60), isRunning(false), fullScreen(false) {
	Debug::Info("SceneManager Constructor", __FILE__, __LINE__);
}

SceneManager::~SceneManager() {
	if (currentScene) {
		currentScene->OnDestroy();
		delete currentScene;
		currentScene = nullptr;
	}
	
	if (timer) {
		delete timer;
		timer = nullptr;
	}

	if (window) {
		delete window;
		window = nullptr;
	}
	Debug::Info("Deleting the GameSceneManager", __FILE__, __LINE__);

}

bool SceneManager::Initialize(std::string name_, int width_, int height_) {

	window = new Window();
	width = width_;
	height = height_;
	
	if (!window->OnCreate(name_, width_, height_)) {
		Debug::FatalError("Failed to initialize Window object", __FILE__, __LINE__);
		return false;
	}
	SDL_SetWindowFullscreen(window->getWindow(), SDL_WINDOW_MINIMIZED);

	timer = new Timer();
	Debug::Info("Creating Timer", __FILE__, __LINE__);
	if (timer == nullptr) {
		Debug::FatalError("Failed to initialize Timer object", __FILE__, __LINE__);
		return false;
	}
	/********************************   Default first scene   ***********************/
	BuildScene(SCENE0); // Change to Main Menu scene
	
	return true;
}


void SceneManager::Run() {
	timer->Start();
	isRunning = true;
	while (isRunning) {
		timer->UpdateFrameTicks();

		// check current scene call designation to change scenes or quit game
		switch (currentScene->callDesignation)	{
		case -1:
			isRunning = false;
			break;
		case 0:
			BuildScene(SCENE0);
			break;
		case 1:
			BuildScene(SCENE1);
			break;
		}

		currentScene->Update(timer->GetDeltaTime());
		currentScene->Render();
		GetEvents();
		SDL_GL_SwapWindow(window->getWindow());
		SDL_Delay(timer->GetSleepTime(fps));
	}
}

void SceneManager::GetEvents() {
	SDL_Event sdlEvent;
	while (SDL_PollEvent(&sdlEvent)) {
		if (sdlEvent.type == SDL_EventType::SDL_QUIT) {
			isRunning = false;
			return;
		}
		
		else if (sdlEvent.type == SDL_KEYDOWN) {
			switch (sdlEvent.key.keysym.scancode) {
			// Quit should open a menue not outright exit (Remove)
			case SDL_SCANCODE_ESCAPE:
			case SDL_SCANCODE_Q:
				isRunning = false;
				return;

			// Change fullscreen key
			case SDL_SCANCODE_RETURN:
				fullScreen = !fullScreen;
				if (fullScreen) {SDL_SetWindowFullscreen(window->getWindow(), SDL_WINDOW_FULLSCREEN);}
				else {SDL_SetWindowFullscreen(window->getWindow(), SDL_WINDOW_MINIMIZED);}
				

			default:
				currentScene->HandleEvents(sdlEvent);
				break;
			}
		}
		if (currentScene == nullptr) {
			Debug::FatalError("Failed to initialize Scene", __FILE__, __LINE__);
			isRunning = false;
			return;
		}
		
		currentScene->HandleEvents(sdlEvent);
	}
}

// Called by UI elements to change or reload scene
void SceneManager::BuildScene(SCENE_NUMBER scene) {
	bool status; 

	if (currentScene != nullptr) {
		delete currentScene;
		currentScene = nullptr;
	}

	switch (scene) {
	case SCENE0:
		currentScene = new MainMenu();
		status = currentScene->OnCreate();
		break;

	case SCENE1:
		currentScene = new TestLevel();
		status = currentScene->OnCreate();
		break;

	// Add More Scenes Here

	default:
		Debug::Error("Incorrect scene number assigned in the manager", __FILE__, __LINE__);
		currentScene = nullptr;
		break;
	}	

	if (currentScene != nullptr) {
		currentScene->screenWidth = width;
		currentScene->screenHeight = height;
		currentScene->callDesignation = -100;
	}
}


