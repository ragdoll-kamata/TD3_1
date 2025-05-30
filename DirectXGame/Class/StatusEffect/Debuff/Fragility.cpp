#include "Fragility.h"

void Fragility::PeculiarInitialize() {
	effectTiming_ = EffectTiming::BeforeDefense;
	stackDecreaseTiming_ = StackDecreaseTiming::EndOfTurn;
}

void Fragility::ApplyEffect() {
	status_->SetDamageRate(status_->GetDamageRate() * 1.5f);
}
