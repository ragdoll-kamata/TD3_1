#include "DrawAttack.h"
#include "CardManager.h"
void DrawAttack::IndividualInitialize() {
	luck = 1;
	reverseLuck = -1;
	sprite.SetColor({0.9f, 0.9f, 1.0f, 1.0f});
	cardType = CardType::Damage;
	cardRange = CardRange::One;
	id = 15;
}

bool DrawAttack::Effect() {
	battleManager_->DamageEnemy(8, targetEnemy, playerStatus_);
	cardManager_->CardDraw(1);

	return true;
}

bool DrawAttack::ReverseEffect() {
	battleManager_->HealEnemy(8, targetEnemy, playerStatus_);
	cardManager_->CardDraw(1);
	return true;
}
