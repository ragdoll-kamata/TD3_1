#include "StandardAtack.h"

void StandardAtack::Initialize() { 
	Card::Initialize();
	luck = 1;
	rverseLuck = -1;
	cardType = CardType::Damage;
	cardRange = CardRange::One;
}

void StandardAtack::Effect() {}

void StandardAtack::ReverseEffect() {}
