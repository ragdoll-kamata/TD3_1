#include "SceneManager.h"

SceneManager* SceneManager::instance = nullptr;
void SceneManager::Initialize() { 
	sceneFactory = new SceneFactory; 
	blackout = new Blackout;
	blackout->Initialize();
}

void SceneManager::Update() {
	if (nextScene) {
		if (!blackout->GetIsStart() || blackout->GetIsMiddle()) {
			if (activeScene) {
				delete activeScene;
			}

			activeScene = nextScene;
			nextScene = nullptr;
			activeScene->Initialize(blackout);
		}
	}
	activeScene->Update();
	blackout->Update();
}

void SceneManager::Draw() {
	activeScene->Draw();
	blackout->Draw();
}

void SceneManager::SetNextScene(SceneName sceneName) {
	nextScene = sceneFactory->CreateScene(sceneName);
}

SceneManager* SceneManager::GetInstance() {
	if (instance == nullptr) {
		instance = new SceneManager;
	}
	return instance;
}

void SceneManager::Finalize() { 
	delete instance;
	instance = nullptr;
}
