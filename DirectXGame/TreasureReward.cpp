#include "TreasureReward.h"
#include "RelicManager.h"
void TreasureReward::Initialize(CardManager* cardManager, RelicManager* relicManager) {
	Reward::Initialize(cardManager, relicManager);
	relicManager_ = relicManager;
	relic = relicManager_->CreateRandomRelic();
}

void TreasureReward::Update() {

	Reward::Update();
	if (isR) {
		relicManager_->AddRelic(std::move(relic));
		isD = true;
	}
}

