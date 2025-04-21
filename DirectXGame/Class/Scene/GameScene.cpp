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

	rewardManager_ = std::make_unique<RewardManager>();
	rewardManager_->Initialize(cardManager_.get());
	battleManager_->SetRewardManager(rewardManager_.get());

	cardManager_->StartCreateSDeck();

	mapManager_ = std::make_unique<MapManager>();
	mapManager_->Initialize(battleManager_.get(), rewardManager_.get());
	mapManager_->CreateMap();
	rewardManager_->SetMapManager(mapManager_.get());

	battleManager_->SetMapManager(mapManager_.get());

	uiManager_ = std::make_unique<UIManager>();
	uiManager_->Initialize(player_.get(), cardManager_.get(), mapManager_.get());

	relicManager_ = std::make_unique<RelicManager>();
	relicManager_->Initialize(cardManager_.get(), battleManager_.get());
	cardManager_->SetRelicManager(relicManager_.get());
}

void GameScene::Update() {
	uiManager_->Update();
	mapManager_->Update();
	if (!uiManager_->IsSDeckOpen()) {
		if (!mapManager_->GetIsMapOpen()) {
			battleManager_->Update();
			rewardManager_->Update();
		}
		mapManager_->CollisionUpdata();
	}
	enemyManager_->Update();
	relicManager_->Update();
}


void GameScene::Draw() {

	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = dxCommon_->GetCommandList();
#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);


	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	battleManager_->Draw();
	rewardManager_->Draw();

	relicManager_->Draw();

	mapManager_->Draw();

	uiManager_->Draw();

	// スプライト描画後処理
	Sprite::PostDraw();

#pragma endregion
}

void GameScene::Destroy() { 


	delete camera_;

}
