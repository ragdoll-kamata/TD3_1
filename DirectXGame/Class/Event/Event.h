#pragma once
#include "RewardManager.h"
#include "CardManager.h"
#include "Player.h"
class Event {
public:
	virtual ~Event() = default;
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

	void SetCardManager(CardManager* cardManager) { cardManager_ = cardManager; }
	void SetPlayer(Player* player) { player_ = player; }

protected:
	RewardManager* rewardManager_ = nullptr;
	CardManager* cardManager_ = nullptr;
	Player* player_ = nullptr;
	bool isEnd = false;
};
