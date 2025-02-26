#include "StandardAtack.h"

void StandardAtack::Initialize() { 
	Card::Initialize();
	luck = 1;
	rverseLuck = -1;
}

void StandardAtack::Effect() {}

void StandardAtack::ReverseEffect() {}
