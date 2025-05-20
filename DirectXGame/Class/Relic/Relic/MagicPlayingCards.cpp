#include "MagicPlayingCards.h"
#include "CardManager.h"
void MagicPlayingCards::PeculiarInitialize() {
	effectTiming_ = RelicEffectTiming::StartOfBattle;
	isStack_ = false;
}

void MagicPlayingCards::ApplyEffect() { cardManager_->AddDrawNum(2); }