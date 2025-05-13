#include "StandardRiskyAttack.h"

void StandardRiskyAttack::IndividualInitialize() {
	luck = 1;
	reverseLuck = -1;
	sprite.SetColor({1.0f, 0.7f, 0.7f, 1.0f});
	cardType = CardType::Damage;
	cardRange = CardRange::One;
	id = 1;
	value = 10;
}

bool StandardRiskyAttack::Effect() {
	battleManager_->DamageEnemy(value, targetEnemy, playrStatus_);
	battleManager_->ShieldPlayer(-value / 2, playrStatus_);
	return true;
}

bool StandardRiskyAttack::ReverseEffect() {
	battleManager_->HealEnemy(value, targetEnemy, playrStatus_);
	battleManager_->ShieldPlayer(value / 2, playrStatus_);
	return true;
}
