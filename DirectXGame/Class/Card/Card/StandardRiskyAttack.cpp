#include "StandardRiskyAttack.h"

void StandardRiskyAttack::IndividualInitialize() {
	TH = TextureManager::GetInstance()->Load("card/StanderdRiskyAttack.png");
	sprite.SetTextureHandle(TH);
	luck = 1;
	reverseLuck = -1;
	//sprite.SetColor({1.0f, 0.7f, 0.7f, 1.0f});
	cardType = CardType::Damage;
	cardRange = CardRange::One;
	id = 1;
	value = 12;
}

bool StandardRiskyAttack::Effect() {
	battleManager_->DamageEnemy(value, targetEnemy, playerStatus_);
	battleManager_->ShieldPlayer(-value / 2, playerStatus_);
	return true;
}

bool StandardRiskyAttack::ReverseEffect() {
	battleManager_->HealEnemy(value, targetEnemy, playerStatus_);
	battleManager_->ShieldPlayer(value / 2, playerStatus_);
	return true;
}
