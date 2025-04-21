#pragma once
#include "Reward.h"
#include <memory>
#include <vector>
#include <functional>
#include "Button.h"
#include "BattleEnemyType.h"
class CardManager;
class MapManager;
class RewardManager {
public:

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(CardManager* cardManager);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();


	void CreateBattleReward(BattleEnemyType battleEnemyType);

	bool IsReward() const { return isReward; }

	bool IsSkip() const { return isSkip; }

	void SetIsReward(bool is) { isReward = is; }

	void ClearReward();

	void SetMapManager(MapManager* mapManager) { mapManager_ = mapManager; }

private:
	void CreateBattleNormalReward();
	void CreateBattleEliteReward();
	void CreateBattleBossReward();

private:
	std::unordered_map<BattleEnemyType, std::function<void()>> fCreateReward{
	    {BattleEnemyType::Normal, std::bind(&RewardManager::CreateBattleNormalReward, this)},
	    {BattleEnemyType::Elite,  std::bind(&RewardManager::CreateBattleEliteReward,  this)},
	    {BattleEnemyType::Boss,   std::bind(&RewardManager::CreateBattleBossReward,   this)}
    };


	Sprite back;
	Button skip;
	bool isReward = false;
	bool isSkip = false;
	bool is_ = false;
	CardManager* cardManager_ = nullptr;
	std::vector<std::unique_ptr<Reward>> rewards;

	MapManager* mapManager_ = nullptr;
};
