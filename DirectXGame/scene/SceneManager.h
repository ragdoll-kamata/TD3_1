#pragma once
#include "Scene.h"
#include "SceneName.h"
#include "SceneFactory.h"
#include "Blackout.h"

class SceneManager {
public:
	void Initialize();

	// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void SetNextScene(SceneName sceneName);

	static SceneManager* GetInstance();
	void Finalize();

private:
	static SceneManager* instance;

	Scene* activeScene = nullptr;
	Scene* nextScene = nullptr;

	SceneFactory* sceneFactory = nullptr;

	Blackout* blackout = nullptr;

	SceneManager() = default;
	~SceneManager() = default;
	SceneManager(SceneManager&) = default;
	SceneManager& operator=(SceneManager&) = default;
};
