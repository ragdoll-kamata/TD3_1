#include "CardReward.h"
#include "CardManager.h"
void CardReward::Initialize(CardManager* cardManager) {
	Reward::Initialize(cardManager);
	cardManager_ = cardManager;
	reward = cardManager->RewardCardGeneration();
}

void CardReward::Update() {
	Vector2 mousePos = Input::GetInstance()->GetMousePosition();

	if (isR) {
		for (int i = 0; i < reward.size(); i++) {
			if (reward[i]->IsOnCollision(mousePos)) {
				if (Input::GetInstance()->IsTriggerMouse(0)) {
					reward[i]->SetSize(1.0f);
					cardManager_->AddSDeck(std::move(reward[i]));
					reward.clear();
					isD = true;
				}
			}
		}
	} else {
		Reward::Update();
	}
}

void CardReward::CardDraw() {
	if (isR) {
		for (int i = 0; i < reward.size(); i++) {
			reward[i]->Draw();
		}
	}
}
