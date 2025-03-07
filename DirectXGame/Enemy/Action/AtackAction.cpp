#include "AtackAction.h"

void AtackAction::Execute() { battleManager_->DamagePlayer(value_); }
