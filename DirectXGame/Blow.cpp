#include "Blow.h"
#include "StatusEffectFactory.h"
void Blow::IndividualInitialize() {
	luck = 2;
	rverseLuck = -2;
	sprite.SetColor({1.0f, 0.0f, 0.0f, 1.0f});
	cardType = CardType::Damage;
	cardRange = CardRange::One;
	id = 5;
	value = 8;
}

bool Blow::Effect() {
	battleManager_->DamageEnemy(value, targetEnemy, playrStatus_);
	battleManager_->StatusEffectEnemy(targetEnemy, std::move(StatusEffectFactory::CreateStatusEffect("Fragility")), 2);
	return true;
}

bool Blow::ReverseEffect() { return false; }
