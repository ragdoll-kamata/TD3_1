#pragma once
#include <chrono>
#include <list>
#include <memory>

#include <KamataEngine.h>
using namespace KamataEngine;

#include "Scene.h"
#include "CardManager.h"
#include "EnemyManager.h"
#include "Player.h"
#include "BattleManager.h"
#include "RewardManager.h"
#include "MapManager.h"
#include "UIManager.h"
#include "RelicManager.h"
#include "EventManager.h"
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

	void Destroy() override;

	Camera skyDomeCamera_;


private: // メンバ変数

	/// <summary>
	/// ゲームシーン用
	/// </summary>
	
	std::unique_ptr<CardManager> cardManager_ = nullptr;
	std::unique_ptr<EnemyManager> enemyManager_ = nullptr;
	std::unique_ptr<Player> player_ = nullptr;
	std::unique_ptr<BattleManager> battleManager_ = nullptr;
	std::unique_ptr<RewardManager> rewardManager_ = nullptr;
	std::unique_ptr<UIManager> uiManager_ = nullptr;
	std::unique_ptr<RelicManager> relicManager_ = nullptr;
	std::unique_ptr<EventManager> eventManager_ = nullptr;

	std::unique_ptr<MapManager> mapManager_ = nullptr;
	// カメラ
	Camera* camera_ = nullptr;
	bool isClear;


	bool isDelta = true;
	bool isEnd = false;
};
