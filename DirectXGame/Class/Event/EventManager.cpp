#include "EventManager.h"
#include "TreasureEvent.h"
#include "RestEvent.h"
#include "MapManager.h"
void EventManager::Initialize(RewardManager* rewardManager) {
		this->rewardManager_ = rewardManager;
}
void EventManager::Update() {
	if (event) {
		event->Update();
		if (event->IsEnd()) {
			mapManager_->SetIsMapOpen(true);
			mapManager_->SetIsMove(true);
			event.reset();
		}
	}
}

void EventManager::Draw() {
	if (event) {
		event->Draw();
	}
}

void EventManager::CreateRestEvent() {
	event = std::make_unique<RestEvent>();
	event->Initialize(rewardManager_);
	event->SetCardManager(cardManager_);
	event->SetPlayer(player_);
}

void EventManager::CreateTreasureEvent() {
	event = std::make_unique<TreasureEvent>();
	event->Initialize(rewardManager_);
}
