#include "Weakening.h"

void Weakening::PeculiarInitialize() {
	effectTiming_ = EffectTiming::BeforeAttack;
	stackDecreaseTiming_ = StackDecreaseTiming::StartOfTurn;
}

void Weakening::ApplyEffect() { status_->SetDamageRate(status_->GetDamageRate() * 0.75f); }
