#pragma once
#include <chrono>
#include <list>
#include <memory>

#include <KamataEngine.h>
using namespace KamataEngine;

#include "Scene.h"

/// <summary>
/// ゲームシーン
/// </summary>
class GameScene : public Scene {

public: // メンバ関数
	/// <summary>
	/// コンストクラタ
	/// </summary>
	GameScene();

	/// <summary>
	/// デストラクタ
	/// </summary>
	~GameScene();


	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize2() override;

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	void CheckAllCollisions();

	void GenerateBlocks();

	void Destroy() override;

	Camera skyDomeCamera_;


private: // メンバ変数

	/// <summary>
	/// ゲームシーン用
	/// </summary>


	// カメラ
	Camera* camera_ = nullptr;
	bool isClear;


	bool isDelta = true;
	bool isEnd = false;
};
