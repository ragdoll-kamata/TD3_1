#include "RewardManager.h"
#include "CardReward.h"
void RewardManager::Initialize(CardManager* cardManager) {
	cardManager_=cardManager;

}

void RewardManager::Update() {
	if (IsReward()) {
		bool is = false;
		for (int i = 0; i < rewards.size(); i++) {
			rewards[i]->SetIs(false);
			is = rewards[i]->GetIs();
		}
		if (is) {
			for (int i = 0; i < rewards.size(); i++) {
				rewards[i]->SetIs(true);
			}
		}
		for (int i = 0; i < rewards.size(); i++) {
			rewards[i]->SetPos({640.0f, 300 + 41.0f * i});
			rewards[i]->Update();
		}
		std::erase_if(rewards, [](const auto& a) { return a->IsDelete(); });
	} 

}

void RewardManager::Draw() {
	for (int i = 0; i < rewards.size(); i++) {
		rewards[i]->Draw();
	}
	for (int i = 0; i < rewards.size(); i++) {
		rewards[i]->CardDraw();
	}
}

void RewardManager::CreateBattleReward() {
	rewards.push_back(std::make_unique<CardReward>());
	for (int i = 0; i < rewards.size(); i++) {
		rewards[i]->Initialize(cardManager_);
	}

}
