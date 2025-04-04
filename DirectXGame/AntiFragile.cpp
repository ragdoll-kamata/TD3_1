#include "AntiFragile.h"

void AntiFragile::PeculiarInitialize() {
	effectTiming_ = EffectTiming::BeforeDefense;
	stackDecreaseTiming_ = StackDecreaseTiming::StartOfTurn;
}

void AntiFragile::ApplyEffect() {
	status_->SetDamageRate(status_->GetDamageRate() * 0.75f);
}
