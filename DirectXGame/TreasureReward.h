#pragma once
#include "Reward.h"
#include "Relic.h"
class TreasureReward : public Reward {
public:
	/// <summary>
	/// イベント初期化
	/// </summary>
	void Initialize(CardManager* cardManager, RelicManager* relicManager) override;
	/// <summary>
	/// イベント更新
	/// </summary>
	void Update() override;
	/// <summary>
	/// イベント描画
	/// </summary>
	void Draw() override;

private:
	RelicManager* relicManager_ = nullptr;
	std::unique_ptr<Relic> relic;
};
