#include "ShieldAction.h"

void ShieldAction::Execute() { battleManager_->ShieldEnemy(value_, enemy_, status_); }
