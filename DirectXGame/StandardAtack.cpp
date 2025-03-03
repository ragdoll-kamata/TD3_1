#include "StandardAtack.h"
#include "Enemy.h"
void StandardAtack::Initialize() { 
	Card::Initialize();
	luck = 1;
	rverseLuck = -1;
	cardType = CardType::Damage;
	cardRange = CardRange::One;
	id = 1;
	value = 5;
}

bool StandardAtack::Effect() { 
	targetEnemy->DamageHP(value);
	return true;
}

bool StandardAtack::ReverseEffect() { 
	targetEnemy->DamageHP(-value); 
	return true;
}
