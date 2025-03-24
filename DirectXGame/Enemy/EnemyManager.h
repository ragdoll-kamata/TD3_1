#pragma once
#include <memory>
#include <vector>
#include <random>
#include "Enemy.h"
#include <math/Vector2.h>
#include "EnemyFactory.h"
#include "EffectTiming.h"
#include "StackDecreaseTiming.h"
using namespace KamataEngine;

class BattleManager;

class EnemyManager {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	bool StartMainTurn();

	bool MainTurn();

	bool EndMainTurn();

	void StartBattle();

	bool GetIsEnemyTurn() const { return isEnemyTurn; }

	void CreateEnemy();

	uint32_t IsOnCollision(Vector2 pos);

	uint32_t GetRadomEnemy();

	Enemy* GetEnemy(const uint32_t& EH);

	int GetEnemyCount() const { return static_cast<int>(enemy.size()); }

	void SetBattleManager(BattleManager* battleManager) { battleManager_ = battleManager; }

	void Effect(EffectTiming effectTiming, StackDecreaseTiming stackDecreaseTiming);

private:
	// シャッフルのための乱数エンジンを用意
	std::mt19937 g; // メルセンヌ・ツイスタ（高品質な乱数生成）


	std::vector<std::unique_ptr<Enemy>> enemy;
	std::unique_ptr<EnemyFactory> enmeyFactory_;
	bool isEnemyTurn = false;

	BattleManager* battleManager_ = nullptr;

};
