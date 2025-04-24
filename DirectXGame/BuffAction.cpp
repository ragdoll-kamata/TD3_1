#include "BuffAction.h"
#include "StatusEffectFactory.h"

void BuffAction::Execute() { battleManager_->StatusEffectEnemy(enemy_, StatusEffectFactory::CreateStatusEffect(statusEffectName_), stack_); }
