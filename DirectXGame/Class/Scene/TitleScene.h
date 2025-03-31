#pragma once
#include "Scene.h"
class TitleScene : public Scene
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

	uint32_t GH_;
	Sprite* sprite;
	uint32_t GH2_;
	Sprite* sprite2;
	uint32_t GH3_;
	Sprite* sprite3;
	bool isSousa;
	bool isSousa2;
};

