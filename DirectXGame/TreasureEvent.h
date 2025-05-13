#pragma once
#include "Event.h"
#include <memory>
#include "Button.h" 
class TreasureEvent : public Event {
public:
	~TreasureEvent() override;
	/// <summary>
	/// イベント初期化
	/// </summary>
	void Initialize(RewardManager* rewardManager) override;
	/// <summary>
	/// イベント更新
	/// </summary>
	void Update() override;
	/// <summary>
	/// イベント描画
	/// </summary>
	void Draw() override;

private:
	std::unique_ptr<Button> treasureButton;
};
