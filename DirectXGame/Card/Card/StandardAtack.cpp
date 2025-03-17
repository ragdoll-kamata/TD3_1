#include "StandardAtack.h"
#include "Enemy.h"
void StandardAtack::IndividualInitialize() { 
	luck = 1;
	rverseLuck = -1;
	cardType = CardType::Damage;
	cardRange = CardRange::One;
	id = 1;
	value = 5;
}

bool StandardAtack::Effect() { 
	battleManager_->DamageEnemy(value, targetEnemy, playrStatus_);
	return true;
}

bool StandardAtack::ReverseEffect() { 
	battleManager_->DamageEnemy(-value, targetEnemy, playrStatus_);
	return true;
}
