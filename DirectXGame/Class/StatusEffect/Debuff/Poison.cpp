#include "Poison.h"
#include "BattleManager.h"

Poison::~Poison() {}

void Poison::PeculiarInitialize() {
	effectTiming_ = EffectTiming::EndOfTurn;
	stackDecreaseTiming_ = StackDecreaseTiming::OnEffect;
}

void Poison::ApplyEffect() { 
	status_->ApplyDirectDamage(stack_);
}
