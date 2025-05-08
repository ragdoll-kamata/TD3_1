#pragma once
#include <memory>

#include "Event.h"
class EventManager {
public:
	/// <summary>
	/// イベント初期化
	/// </summary>
	void Initialize();
	/// <summary>
	/// イベント更新
	/// </summary>
	void Update();
	/// <summary>
	/// イベント描画
	/// </summary>
	void Draw();

	void CreateRandomEvent();

	void CreateRestEvent();

	void CreateTreasureEvent();

private:
	std::unique_ptr<Event> event;
};
