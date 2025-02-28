#include "StandardShield.h"

void StandardShield::Initialize() {
	Card::Initialize();
	luck = 1;
	rverseLuck = -1;
	sprite.SetColor({0.0f, 1.0f, 1.0f, 1.0f});
	cardType = CardType::Shield;
	cardRange = CardRange::Self;
}

void StandardShield::Effect() {}

void StandardShield::ReverseEffect() {}
