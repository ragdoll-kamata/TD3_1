#include "StandardShield.h"
#include "Player.h"
void StandardShield::Initialize() {
	Card::Initialize();
	luck = 1;
	rverseLuck = -1;
	sprite.SetColor({0.0f, 1.0f, 1.0f, 1.0f});
	cardType = CardType::Shield;
	cardRange = CardRange::Self;
	id = 2;
}

bool StandardShield::Effect() { 
	player_->AddShield(5);
	return true; 
}

bool StandardShield::ReverseEffect() { 
	player_->Damage(5);
	return true;
}
