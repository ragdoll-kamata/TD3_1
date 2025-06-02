#include "StandardAtack.h"
#include "Enemy.h"
void StandardAtack::IndividualInitialize() {
	TH = TextureManager::GetInstance()->Load("card/StanderdAttack.png");
	sprite.SetTextureHandle(TH);
	luck = 1;
	reverseLuck = -1;
	cardType = CardType::Damage;
	cardRange = CardRange::One;
	id = 0;
	value = 6;
}

bool StandardAtack::Effect() { 
	battleManager_->DamageEnemy(value, targetEnemy, playerStatus_);
	return true;
}

bool StandardAtack::ReverseEffect() { 
	battleManager_->DamageEnemy(-value, targetEnemy, playerStatus_);
	return true;
}
