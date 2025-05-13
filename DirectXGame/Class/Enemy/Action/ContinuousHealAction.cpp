#include "ContinuousHealAction.h"

void ContinuousHealAction::Execute() {
	for (int i = 0; i < value2_; i++) {
		battleManager_->HealEnemy(value_, enemy_, status_);
	}
}
