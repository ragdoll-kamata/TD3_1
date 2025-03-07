#pragma once
#include <memory>
#include <vector>
#include "Enemy.h"
#include <math/Vector2.h>
#include "EnemyFactory.h"
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

	Enemy* GetEnemy(const uint32_t& EH);

	void SetBattleManager(BattleManager* battleManager) { battleManager_ = battleManager; }

private:
	std::vector<std::unique_ptr<Enemy>> enemy;
	std::unique_ptr<EnemyFactory> enmeyFactory_;
	bool isEnemyTurn = false;

	BattleManager* battleManager_ = nullptr;

};
