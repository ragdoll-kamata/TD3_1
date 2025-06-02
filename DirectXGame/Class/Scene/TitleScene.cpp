#include "TitleScene.h"
#include "SceneManager.h"

void TitleScene::Initialize2() {
	button = std::make_unique<Button>();
	button->Initialize({640.0f, 360.0f}, {1280.0f, 720.0f}, "back/backScreen.png", {1.0f, 1.0f, 1.0f, 1.0f});
	button->SetTextureRect({1920.0f, 1080.0f});
	uint32_t th = TextureManager::GetInstance()->Load("back/title.png");
	sprite = Sprite::Create(th, {});
	sprite->SetColor({0.7f, 0.7f, 0.7f, 1.0f});
}

void TitleScene::Update() { 
	if (input_->IsTriggerMouse(0)) {
		if (button->IsOnCollision(input_->GetMousePosition())) {
			if (blackout_->GetIsEnd()) {
				blackout_->SetIsStart(true);
				SceneManager::GetInstance()->SetNextScene(SceneName::GameScene);
			}
		}
	}
}

void TitleScene::Draw()
{

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();
#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>
	button->Draw();
	sprite->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();
}

void TitleScene::Destroy() { 
	delete sprite;

}
