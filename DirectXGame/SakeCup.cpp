#include "SakeCup.h"
#include "CardManager.h"
void SakeCup::PeculiarInitialize() { 
	effectTiming_ = RelicEffectTiming::Play;
	isStack_ = true;
}

void SakeCup::ApplyEffect() {
	if (cardManager_->GetExecutionCardType() == CardType::Skill) {
		stack_++;
		if (stack_ >= 5) {
			cardManager_->CardDraw(2);
			stack_ = 0;
		}
	}
}
