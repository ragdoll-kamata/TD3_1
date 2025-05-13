#include "TreasureEvent.h"

TreasureEvent::~TreasureEvent() {
	rewardManager_->ClearReward();
}

void TreasureEvent::Initialize(RewardManager* rewardManager) {
	Event::Initialize(rewardManager);
	treasureButton = std::make_unique<Button>();
	treasureButton->Initialize({640.0f, 360.0f}, {200.0f, 100.0f}, "white1x1.png", {1.0f, 1.0f, 1.0f, 1.0f});

}

void TreasureEvent::Update() {
	if (Input::GetInstance()->IsTriggerMouse(0)) {
		Vector2 mousePos = Input::GetInstance()->GetMousePosition();
		if (treasureButton->IsOnCollision(mousePos)) {
			if (!rewardManager_->IsReward()) {
				rewardManager_->CreateTreasureReward();
			} else {
				if (!rewardManager_->GetSelect()) {
					rewardManager_->SelectTrue();
				}
			}
		}
	}
	if (rewardManager_->IsSkip()) {
		if (!rewardManager_->GetSelect()) {
			isEnd = true;
		}
	}
}

void TreasureEvent::Draw() {
	treasureButton->Draw();

}
