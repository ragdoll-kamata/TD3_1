#include "CardReward.h"
#include "CardManager.h"
void CardReward::Initialize(CardManager* cardManager, RelicManager* relicManager) {
	Reward::Initialize(cardManager, relicManager);
	cardManager_ = cardManager;
	relicManager;
	reward = cardManager->RewardCardGeneration();
	button.Initialize({640.0f, 550.0f}, {200.0f,50.0f}, "white1x1.png", {1.0f, 1.0f, 1.0f, 1.0f});
}

void CardReward::Update() {
	Vector2 mousePos = Input::GetInstance()->GetMousePosition();

	if (isR) {
		if (Input::GetInstance()->IsTriggerMouse(0)) {
			for (int i = 0; i < reward.size(); i++) {
				if (reward[i]->IsOnCollision(mousePos)) {
					reward[i]->SetSize(1.0f);
					cardManager_->AddSDeck(std::move(reward[i]));
					reward.clear();
					isD = true;
				}
			}

			if (button.IsOnCollision(mousePos)) {
				isR = false;
			}
		}
	}

	Reward::Update();
}

void CardReward::CardDraw() {
	if (isR) {
		for (int i = 0; i < reward.size(); i++) {
			reward[i]->Draw();
		}
		button.Draw();
	}
	
}
