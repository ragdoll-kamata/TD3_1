#include "Over.h"
#include "SceneManager.h"

void Over::Initialize2() {
	button = std::make_unique<Button>();
	button->Initialize({640.0f, 360.0f}, {1280.0f, 720.0f}, "back/gameover.png", {1.0f, 1.0f, 1.0f, 1.0f});
	button->SetTextureRect({1280.0f, 720.0f});
	// SH_ = audio_->LoadWave("audio/GameOverBGM.mp3");

	// VH_ = audio_->PlayWave(SH_, true, 0.5f);
}

void Over::Update() {

	if (input_->IsTriggerMouse(0)) {
		if (button->IsOnCollision(input_->GetMousePosition())) {
			if (blackout_->GetIsEnd()) {
				blackout_->SetIsStart(true);
				SceneManager::GetInstance()->SetNextScene(SceneName::TitleScene);
			}
		}
	}

	if (blackout_->GetIsStart() && blackout_->GetIsMiddle()) {
		isFinish = true;
		//audio_->StopWave(VH_);
	}
}

void Over::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	button->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();
}

void Over::Destroy() { }
