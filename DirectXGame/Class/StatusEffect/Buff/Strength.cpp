#include "Strength.h"

void Strength::PeculiarInitialize() {
	effectTiming_ = EffectTiming::BonusDamage;
	stackDecreaseTiming_ = StackDecreaseTiming::NotDecrease;
}

void Strength::ApplyEffect() { status_->SetBonusDamage(stack_); }
