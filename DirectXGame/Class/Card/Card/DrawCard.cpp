#include "DrawCard.h"
#include "CardManager.h"

void DrawCard::IndividualInitialize() {
	luck = 2;
	reverseLuck = -4;
	cardType = CardType::Skill;
	cardRange = CardRange::Self;
	id = 12;
	sprite.SetColor({1.0f, 0.5f, 0.0f, 1.0f});
}

bool DrawCard::Effect() {

	cardManager_->CardDraw(2);
	return true;
}

bool DrawCard::ReverseEffect() { 
	int i = cardManager_->RandomHandDeath(2);
	for (int j = 0; j < i; j++) {
		battleManager_->DamagePlayer(3, nullptr);
	}
	return true;
}
