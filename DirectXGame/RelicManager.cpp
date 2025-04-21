#include "RelicManager.h"
#include "MagicPlayingCards.h"
#include "SakeCup.h"
void RelicManager::Initialize(CardManager* cardManager, BattleManager* battleManager) {
	this->cardManager_ = cardManager;
	this->battleManager_ = battleManager;
	relics.push_back(std::make_unique<MagicPlayingCards>());
	relics.push_back(std::make_unique<SakeCup>());
	for (const auto& relic : relics) {
		relic->Initialize(cardManager_, battleManager_);
	}
}

void RelicManager::Update() {
	int i = 0;
	for (const auto& relic : relics) {
		relic->Update();
		relic->SetPos({46.0f * i, 40.0f});
		i++;
	}
}

void RelicManager::Draw() {
	for (const auto& relic : relics) {
		relic->Draw();
	}
}

void RelicManager::RelicEffect(RelicEffectTiming effectTiming) {
	for (const auto& relic : relics) {
		relic->Effect(effectTiming);
	}
}
