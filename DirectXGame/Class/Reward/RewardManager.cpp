#include "RewardManager.h"
#include "CardReward.h"
#include "MapManager.h"
void RewardManager::Initialize(CardManager* cardManager) {
	cardManager_=cardManager;
	back.Initialize();
	back.SetSize({1280.0f, 720.0f});
	back.SetColor({0.0f, 0.0f, 0.0f, 0.9f});
	skip.Initialize({900.0f, 360.0f}, {200.0f, 50.0f}, "white1x1.png", {1.0f, 1.0f, 1.0f, 1.0f});
}

void RewardManager::Update() {
	if (isReward) {
		is_ = false;
		for (int i = 0; i < rewards.size(); i++) {
			rewards[i]->SetIsU(false);
			is_ = rewards[i]->GetIsR();
			if (is_) {
				break;
			}
		}
		if (is_) {
			for (int i = 0; i < rewards.size(); i++) {
				rewards[i]->SetIsU(true);
			}
		}
		for (int i = 0; i < rewards.size(); i++) {
			rewards[i]->SetPos({640.0f, 300 + 41.0f * i});
			rewards[i]->Update();
		}
		std::erase_if(rewards, [](const auto& asd) { return asd->IsDelete(); });
		if (Input::GetInstance()->IsTriggerMouse(0)) {
 			if (skip.IsOnCollision(Input::GetInstance()->GetMousePosition())) {
				mapManager_->SetIsMapOpen(true);
				mapManager_->SetIsMove(true);
				isSkip = true;
			}
		}
	} 

}

void RewardManager::Draw() {
	if (IsReward()) {
		skip.Draw();
		for (int i = 0; i < rewards.size(); i++) {
			rewards[i]->Draw();
		}
		if (is_) {
			back.Draw();
		}
		for (int i = 0; i < rewards.size(); i++) {
			rewards[i]->CardDraw();
		}
	}
}

void RewardManager::CreateBattleReward(BattleEnemyType battleEnemyType) {
	fCreateReward[battleEnemyType]();
	for (int i = 0; i < rewards.size(); i++) {
		rewards[i]->Initialize(cardManager_);
	}

	isReward = true;
	isSkip = false;
}

void RewardManager::ClearReward() {
	rewards.clear();
	isReward = false;
}

void RewardManager::CreateBattleNormalReward() {
	rewards.push_back(std::make_unique<CardReward>());
}

void RewardManager::CreateBattleEliteReward() {}

void RewardManager::CreateBattleBossReward() {}
