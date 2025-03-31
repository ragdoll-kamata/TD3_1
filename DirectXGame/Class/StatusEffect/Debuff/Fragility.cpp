#include "Fragility.h"

void Fragility::PeculiarInitialize() {
	effectTiming_ = EffectTiming::BeforeDefense;
	stackDecreaseTiming_ = StackDecreaseTiming::StartOfTurn;
}

void Fragility::ApplyEffect() {
	status_->SetDamageRate(status_->GetDamageRate() * 1.5f);
}
