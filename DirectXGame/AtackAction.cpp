#include "AtackAction.h"
#include "Player.h"
void AtackAction::Execute() { player_->Damage(value_); }
