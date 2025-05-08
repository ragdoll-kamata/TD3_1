#include "StrengthUp.h"
#include "StatusEffectFactory.h"
void StrengthUp::IndividualInitialize() {
	luck = -5;
	reverseLuck = -5;
	sprite.SetColor({1.0f, 0.0f, 0.0f, 1.0f});
	cardType = CardType::Ability;
	cardRange = CardRange::Self;
	id = 6;
	value = 2;
}

bool StrengthUp::Effect() {
	battleManager_->StatusEffectPlayer(StatusEffectFactory::CreateStatusEffect("AuraOfDeath"), value);
	return true;
}

bool StrengthUp::ReverseEffect() { 
	battleManager_->StatusEffectPlayer(StatusEffectFactory::CreateStatusEffect("AuraOfLife"), value);
	return true;
}
