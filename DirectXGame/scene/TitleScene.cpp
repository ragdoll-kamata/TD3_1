#include "TitleScene.h"
#include "SceneManager.h"

void TitleScene::Initialize2() {
	GH_ = TextureManager::Load("backGround/Title.png");
	sprite = Sprite::Create(GH_, { 0, 0 });
	GH2_ = TextureManager::Load("backGround/controlPanel.png");
	sprite2 = Sprite::Create(GH2_, { 0, 0 });
	 GH3_ = TextureManager::Load("backGround/controlPanel_2.png");
	 sprite3 = Sprite::Create(GH3_, { 0, 0 });

	SH_ = audio_->LoadWave("audio/TitleBGM.mp3");

	VH_ = audio_->PlayWave(SH_, true, 0.5f);
	
}

void TitleScene::Update()
{
	input_->GetJoystickState(0, xinput);
	input_->GetJoystickStatePrevious(0, preXinput);
	if (xinput.Gamepad.wButtons == XINPUT_GAMEPAD_A && preXinput.Gamepad.wButtons != XINPUT_GAMEPAD_A|| input_->PushKey(DIK_SPACE)) {
		if (blackout_->GetIsEnd()) {
			if (!isSousa) {
				isSousa = true;
			} else {
				if (!isSousa2) {
					isSousa2 = true;
				}else {
					blackout_->SetIsStart(true);
					SceneManager::GetInstance()->SetNextScene(SceneName::GameScene);
				}
			}
		}
	}
	blackout_->Update();
	if (blackout_->GetIsStart() && blackout_->GetIsMiddle()) {
		isFinish = true;
		audio_->StopWave(VH_);
	}
}

void TitleScene::Draw()
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
	if (isSousa) {
		if (isSousa2) {
			sprite3->Draw();
		} else {
			sprite2->Draw();
		}
	}

	blackout_->Draw();
	// スプライト描画後処理
	Sprite::PostDraw();
}

void TitleScene::Destroy() { 
	delete sprite;
	delete sprite2;
}
