#include "Regeneration.h"

void Regeneration::PeculiarInitialize() {
	effectTiming_ = EffectTiming::EndOfTurn;
	stackDecreaseTiming_ = StackDecreaseTiming::OnEffect;
}

void Regeneration::ApplyEffect() {
	status_->Heal(stack_, status_);
}
