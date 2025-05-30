#include "TreasureReward.h"
#include "RelicManager.h"
#include "Relic.h"
void TreasureReward::Initialize(CardManager* cardManager, RelicManager* relicManager) {
	Reward::Initialize(cardManager, relicManager);
	relicManager_ = relicManager;
	relic = std::move(relicManager_->CreateBlankRelic());
}

void TreasureReward::Update() {

	Reward::Update();
	if (isR) {
		relicManager_->AddRelic(std::move(relic));
		isD = true;
	}
}

void TreasureReward::Draw() {
	Reward::Draw();
	if (isR) {
		relic->Draw();
	}
}

