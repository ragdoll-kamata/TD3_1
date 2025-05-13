#include "AuraOfLife.h"

void AuraOfLife::PeculiarInitialize() {
	effectTiming_ = EffectTiming::BonusDamage;
	stackDecreaseTiming_ = StackDecreaseTiming::NotDecrease;
}

void AuraOfLife::ApplyEffect() { status_->SetBonusDamage(-stack_); }
