#pragma once
#include "Reward.h"
#include <memory>
#include <vector>
class CardManager;
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

	bool IsReward() { return rewards.size() > 0; }

	void SetIsReward(bool is) { isReward = is; }

private:
	bool isReward = false;
	CardManager* cardManager_ = nullptr;
	std::vector<std::unique_ptr<Reward>> rewards;
};
