#include "DrawCard.h"
#include "CardManager.h"

void DrawCard::Initialize() {
	Card::Initialize();
	luck = 2;
	rverseLuck = -4;
	cardType = CardType::Skill;
	cardRange = CardRange::Self;
	id = 3;
	sprite.SetColor({1.0f, 0.5f, 0.0f, 1.0f});
}

bool DrawCard::Effect() {

	cardManager_->CardDraw(2);
	return true;
}

bool DrawCard::ReverseEffect() { 
	cardManager_->RandomHandDeath(2);
	return true;
}
