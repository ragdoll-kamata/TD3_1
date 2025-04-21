#pragma once
class Event {
public:
	/// <summary>
	/// イベント初期化
	/// </summary>
	virtual void Initialize() = 0;
	/// <summary>
	/// イベント更新
	/// </summary>
	virtual void Update() = 0;
	/// <summary>
	/// イベント描画
	/// </summary>
	virtual void Draw() = 0;

	void EndEvent() { isEnd = true; }

protected:
	bool isEnd = false;
};
