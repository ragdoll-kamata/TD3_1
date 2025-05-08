#pragma once
#include "RewardManager.h"
class Event {
public:
	/// <summary>
	/// イベント初期化
	/// </summary>
	virtual void Initialize(RewardManager* rewardManager);
	/// <summary>
	/// イベント更新
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// イベント描画
	/// </summary>
	virtual void Draw() = 0;

	void EndEvent() { isEnd = true; }

	bool IsEnd() const { return isEnd; }

protected:
	RewardManager* rewardManager_ = nullptr;
	bool isEnd = false;
};
