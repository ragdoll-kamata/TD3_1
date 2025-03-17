#include "DebuffAtackAction.h"
#include "StatusEffectFactory.h"
void DebuffAtackAction::Execute() {
	battleManager_->DamagePlayer(value_, status_);
	battleManager_->StatusEffectPlayer(StatusEffectFactory::CreateStatusEffect(statusEffectName_), stack_);
}
