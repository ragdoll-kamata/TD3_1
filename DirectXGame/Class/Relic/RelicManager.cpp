#include "RelicManager.h"

#include "Player.h"

#include <algorithm>

#include "MagicPlayingCards.h"
#include "SakeCup.h"
#include "BlankRelic.h"

void RelicManager::Initialize(CardManager* cardManager, BattleManager* battleManager, Player* player) {
	this->cardManager_ = cardManager;
	this->battleManager_ = battleManager;
	this->player_ = player;
	relicFactory_ = std::make_unique<RelicFactory>();

	//relics.push_back(std::make_unique<MagicPlayingCards>());
	//relics.push_back(std::make_unique<SakeCup>());
	for (const auto& relic : relics) {
		relic->Initialize(cardManager_, battleManager_);
	}
	unCommonProbability = std::max<int>(unCommonMinProbability, unCommonProbability + 5);
	rareProbability = std::max<int>(rareMinProbability, rareProbability + 5);
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

std::unique_ptr<Relic> RelicManager::CreateRandomRelic() { 
	std::unique_ptr<Relic> Relic = relicFactory_->CreateRandomRelic(unCommonProbability, rareProbability);
	Relic->Initialize(cardManager_, battleManager_);
	Relic->SetPlayerStatus(player_->GetStatus());

	unCommonProbability = std::max<int>(unCommonMinProbability, unCommonProbability + 5);
	rareProbability = std::max<int>(rareMinProbability, rareProbability + 5);

	return std::move(Relic); // ムーブ
}

std::unique_ptr<Relic> RelicManager::CreateBlankRelic() {
	std::unique_ptr<Relic> relic = std::make_unique<BlankRelic>();
	relic->Initialize(cardManager_, battleManager_);
	return std::move(relic);
}
