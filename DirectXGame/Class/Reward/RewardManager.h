#pragma once
#include "Reward.h"
#include <memory>
#include <vector>
#include "Button.h"
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


	void CreateBattleReward();

	bool IsReward() const { return isReward; }

	bool IsSkip() const { return isSkip; }

	void SetIsReward(bool is) { isReward = is; }

	void ClearReward();

	void SetMapManager(MapManager* mapManager) { mapManager_ = mapManager; }

private:
	Sprite back;
	Button skip;
	bool isReward = false;
	bool isSkip = false;
	bool is_ = false;
	CardManager* cardManager_ = nullptr;
	std::vector<std::unique_ptr<Reward>> rewards;

	MapManager* mapManager_ = nullptr;
};
