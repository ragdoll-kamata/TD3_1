#include "Clear.h"
#include "SceneManager.h"

void Clear::Initialize2() {

	GH_ = TextureManager::Load("backGround/crearScene.png");
	sprite = Sprite::Create(GH_, { 0, 0 });
	SH_ = audio_->LoadWave("audio/ClearBGM.mp3");

	VH_ = audio_->PlayWave(SH_, true, 0.5f);
}

void Clear::Update()
{
	input_->GetJoystickState(0, xinput);
	input_->GetJoystickStatePrevious(0, preXinput);

	if (xinput.Gamepad.wButtons == XINPUT_GAMEPAD_A && preXinput.Gamepad.wButtons != XINPUT_GAMEPAD_A) {
		if (blackout_->GetIsEnd()) {
			blackout_->SetIsStart(true);
			SceneManager::GetInstance()->SetNextScene(SceneName::TitleScene);
		}
	}
	if (blackout_->GetIsStart() && blackout_->GetIsMiddle()) {
		isFinish = true;
		audio_->StopWave(VH_);
	}
}

void Clear::Draw()
{

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 背景スプライト描画
	// 背景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに背景スプライトの描画処理を追加できる
	/// </summary>

	// スプライト描画後処理
	Sprite::PostDraw();
	// 深度バッファクリア
	dxCommon_->ClearDepthBuffer();
#pragma endregion

#pragma region 3Dオブジェクト描画
	// 3Dオブジェクト描画前処理
	Model::PreDraw(commandList);

	/// <summary>
	/// ここに3Dオブジェクトの描画処理を追加できる
	/// </summary>
	/// 
	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	sprite->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();
}

void Clear::Destroy() { delete sprite; }
