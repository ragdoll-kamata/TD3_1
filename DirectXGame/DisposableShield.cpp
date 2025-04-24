#include "DisposableShield.h"
#include "BattleManager.h"
void DisposableShield::PeculiarInitialize() {
	effectTiming_ = RelicEffectTiming::StartOfTurn;
}

void DisposableShield::ApplyEffect() {
	if (i == 0) {
		battleManager_->ShieldPlayer(10, nullptr);
		i++;
	}
}
