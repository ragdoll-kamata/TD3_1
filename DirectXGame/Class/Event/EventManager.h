#pragma once
#include <memory>

#include "Event.h"
class RewardManager;
class MapManager;
class EventManager {
public:
	/// <summary>
	/// イベント初期化
	/// </summary>
	void Initialize(RewardManager* rewardManager);
	/// <summary>
	/// イベント更新
	/// </summary>
	void Update();
	/// <summary>
	/// イベント描画
	/// </summary>
	void Draw();

	void ClearEvent() { event.reset(); }

	void CreateRandomEvent();

	void CreateRestEvent();

	void CreateTreasureEvent();

	void SetMapManager(MapManager* mapManager) { mapManager_ = mapManager; }

private:
	std::unique_ptr<Event> event;
	RewardManager* rewardManager_ = nullptr;
	MapManager* mapManager_ = nullptr;
};
