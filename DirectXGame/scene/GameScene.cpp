#include "GameScene.h"
#include <cassert>
#include <map>
#include "SceneManager.h"
GameScene::GameScene() {}

GameScene::~GameScene() {}

void GameScene::Initialize2() {

	camera_ = new Camera;
	camera_->Initialize();
	camera_->translation_.x = 25.0f;
	camera_->translation_.y = 17.0f;
	camera_->translation_.z = -44.0f;
	camera_->UpdateMatrix();


	//SH_ = audio_->LoadWave("audio/BattleBGM.mp3");


	//VH_ = audio_->PlayWave(SH_, true, 0.5f);

	player_ = std::make_unique<Player>();
	player_->Initialize();

	enemyManager_ = std::make_unique<EnemyManager>();
	enemyManager_->Initialize();

	cardManager_ = std::make_unique<CardManager>();
	cardManager_->Initialize(enemyManager_.get(), player_.get());

	battleManager_ = std::make_unique<BattleManager>();
	battleManager_->Initialize(player_.get(), cardManager_.get(), enemyManager_.get());
	enemyManager_->SetBattleManager(battleManager_.get());
	cardManager_->SetBattleManager(battleManager_.get());

	cardManager_->StartCreateSDeck();
	

	battleManager_->StartBattle();
}

void GameScene::Update() { 
	battleManager_->Update();
	cardManager_->BattleUpdata();
	enemyManager_->Update();
	player_->Update();
}


void GameScene::Draw() {

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



	// 3Dオブジェクト描画後処理
	Model::PostDraw();
#pragma endregion

#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);


	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	enemyManager_->Draw();

	player_->Draw();

	cardManager_->DrawBattle();


	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::Destroy() { 


	delete camera_;

}
