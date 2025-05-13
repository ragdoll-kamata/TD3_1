#include "AmplifierShield.h"
#include "BattleManager.h"
void AmplifierShield::IndividualInitialize() {
	luck = 1;
	reverseLuck = -1;
	sprite.SetColor({0.5f, 0.5f, 0.5f, 1.0f});
	cardType = CardType::Shield;
	cardRange = CardRange::Self;
	id = 100;
	value = 10;
}

bool AmplifierShield::Effect() {
	battleManager_->ShieldPlayer(value, playrStatus_);
	battleManager_->DamagePlayer(value / 2, playrStatus_);
	return true;
}

bool AmplifierShield::ReverseEffect() {
	battleManager_->ShieldPlayer(-value, playrStatus_);
	battleManager_->HealPlayer(value / 2, playrStatus_);
	return true;
}
