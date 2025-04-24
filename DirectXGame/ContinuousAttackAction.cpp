#include "ContinuousAttackAction.h"

void ContinuousAttackAction::Execute() { 
	for (int i = 0; i < value2_; i++) {
		battleManager_->DamagePlayer(value_, status_);
	}
}
