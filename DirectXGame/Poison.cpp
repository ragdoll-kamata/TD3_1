#include "Poison.h"
#include "BattleManager.h"

void Poison::PeculiarInitialize() {
	effectTiming_ = EffectTiming::EndOfTurn;
	stackDecreaseTiming_ = StackDecreaseTiming::OnEffect;
}

void Poison::ApplyEffect() {
	if (enemy_ != nullptr) {
		battleManager_->DamageEnemy(stack_, enemy_);
	} else {
		battleManager_->DamagePlayer(stack_);
	}
}
