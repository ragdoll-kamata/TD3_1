#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;

#include "Blackout.h"

class Scene {
public:
	~Scene();

	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Blackout* blackout);

	virtual void Initialize2();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw();

	bool IsFinish() { return isFinish; }

	virtual bool IsClear() { return false; }

	virtual void Destroy();

protected:
	Blackout* blackout_;


	DirectXCommon* dxCommon_ = nullptr;
	Input* input_ = nullptr;
	Audio* audio_ = nullptr;

	uint32_t SH_ = 0;
	uint32_t VH_ = 0;


	bool isFinish;
};
