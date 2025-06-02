#pragma once
#include "memory"
#include "Scene.h"
#include "Button.h"
class Clear : public Scene
{
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize2() override;

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void Draw() override;

	void Destroy() override;

private:
	XINPUT_STATE xinput;
	XINPUT_STATE preXinput;

	std::unique_ptr<Button> button;
};

