#pragma once
#include "KamataEngine.h"

using namespace KamataEngine;
class Blackout {
public:

	~Blackout();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	bool GetIsStart() const { return isStart; }
	void SetIsStart(bool a) { isStart = a; }
	bool GetIsMiddle() const { return isMiddle; }
	bool GetIsEnd() const { return isEnd; }

	void SetIsWhite(bool a) { isWhite = a; }

private:

	uint32_t tx;
	Sprite* sp = nullptr;

	bool isStart = false;
	uint32_t startTimer;
	static inline const int kBStartTimer = 60;

	uint32_t middleTiner;
	static inline const int kBMiddleTimer = 60;

	static inline const int kWStartTimer = 90;

	static inline const int kWMiddleTimer = 90;


	bool isMiddle = false;
	bool isEnd = false;
	bool isWhite = false;

};
