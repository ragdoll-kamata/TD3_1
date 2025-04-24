#include "AurOfDeath.h"

void AurOfDeath::PeculiarInitialize() {
	effectTiming_ = EffectTiming::BonusDamage;
	stackDecreaseTiming_ = StackDecreaseTiming::NotDecrease;
}

void AurOfDeath::ApplyEffect() { status_->SetBonusDamage(stack_); }
