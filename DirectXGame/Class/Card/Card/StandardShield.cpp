#include "StandardShield.h"
#include "Player.h"
void StandardShield::IndividualInitialize() {
	luck = 1;
	reverseLuck = -1;
	sprite.SetColor({0.0f, 1.0f, 1.0f, 1.0f});
	cardType = CardType::Shield;
	cardRange = CardRange::Self;
	id = 3;
	value = 5;
}

bool StandardShield::Effect() { 
	battleManager_->ShieldPlayer(value, playrStatus_);
	return true; 
}

bool StandardShield::ReverseEffect() { 
	battleManager_->ShieldPlayer(-value, playrStatus_);
	return true;
}
