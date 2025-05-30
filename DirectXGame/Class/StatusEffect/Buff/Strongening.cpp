#include "Strongening.h"

void Strongening::PeculiarInitialize() {
	effectTiming_ = EffectTiming::BeforeAttack;
	stackDecreaseTiming_ = StackDecreaseTiming::EndOfTurn;
}

void Strongening::ApplyEffect() { status_->SetDamageRate(status_->GetDamageRate() * 1.25f); }
