#include "DebuffAction.h"
#include "StatusEffectFactory.h"

void DebuffAction::Execute() {
	battleManager_->StatusEffectPlayer(StatusEffectFactory::CreateStatusEffect(statusEffectName_), stack_);
}
