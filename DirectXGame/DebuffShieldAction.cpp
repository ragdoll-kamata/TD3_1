#include "DebuffShieldAction.h"

#include "StatusEffectFactory.h"

void DebuffShieldAction::Execute() {
	battleManager_->ShieldEnemy(value_, enemy_, status_);
	battleManager_->StatusEffectPlayer(StatusEffectFactory::CreateStatusEffect(statusEffectName_), stack_);
}
