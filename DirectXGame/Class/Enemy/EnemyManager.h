#pragma once
#include <memory>
#include <vector>
#include <random>
#include "Enemy.h"
#include "math/Vector2.h"
#include "EnemyFactory.h"
#include "EffectTiming.h"
#include "StackDecreaseTiming.h"
#include "BattleEnemyType.h"

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

	void StartBattle(BattleEnemyType battleEnemyType);

	bool GetIsEnemyTurn() const { return isEnemyTurn; }

	void CreateEnemy(BattleEnemyType battleEnemyType);

	uint32_t IsOnCollision(Vector2 pos);

	uint32_t GetRadomEnemy();

	Enemy* GetEnemy(const uint32_t& EH);

	int GetEnemyCount() const { return static_cast<int>(enemy.size()); }

	void SetBattleManager(BattleManager* battleManager) { battleManager_ = battleManager; }

	void Effect(EffectTiming effectTiming, StackDecreaseTiming stackDecreaseTiming);

private:
	void CreateNormalEnemy();
	void CreateEliteEnemy();
	void CreateBossEnemy();

private:
	std::unordered_map<BattleEnemyType, std::function<void()>> fCreateEnemy{
	    {BattleEnemyType::Normal, std::bind(&EnemyManager::CreateNormalEnemy, this)},
	    {BattleEnemyType::Elite,  std::bind(&EnemyManager::CreateEliteEnemy,  this)},
	    {BattleEnemyType::Boss,   std::bind(&EnemyManager::CreateBossEnemy,   this)}
	};
	// シャッフルのための乱数エンジンを用意
	std::mt19937 g; // メルセンヌ・ツイスタ（高品質な乱数生成）


	std::vector<std::unique_ptr<Enemy>> enemy;
	std::unique_ptr<EnemyFactory> enmeyFactory_;
	bool isEnemyTurn = false;

	BattleManager* battleManager_ = nullptr;

};
