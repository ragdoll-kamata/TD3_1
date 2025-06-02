#include "Clear.h"
#include "SceneManager.h"

void Clear::Initialize2() {
	button = std::make_unique<Button>();
	button->Initialize({640.0f, 360.0f}, {1280.0f, 720.0f}, "back/clear.png", {1.0f, 1.0f, 1.0f, 1.0f});
	button->SetTextureRect({1280.0f, 720.0f});
}

void Clear::Update()
{


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

	button->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();
}

void Clear::Destroy() {  }
