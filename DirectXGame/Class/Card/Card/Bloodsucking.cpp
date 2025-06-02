#include "Bloodsucking.h"
#include "Enemy.h"
#include "BattleManager.h"

void Bloodsucking::IndividualInitialize() {
	TH = TextureManager::GetInstance()->Load("card/Bloodsucking.png");
	sprite.SetTextureHandle(TH);
	luck = 1;
	reverseLuck = -1;
	//sprite.SetColor({0.1f, 0.0f, 0.0f, 1.0f});
	cardType = CardType::Damage;
	cardRange = CardRange::One;
	id = 100;
	value = 8;
}

bool Bloodsucking::Effect() { 
	int i = targetEnemy->GetStatus()->GetHP();
	battleManager_->DamageEnemy(value, targetEnemy, playerStatus_);
	i -= targetEnemy->GetStatus()->GetHP();

	if (i > 0) {
		battleManager_->HealPlayer(i / 2, playerStatus_);
	}

	return true; 
}

bool Bloodsucking::ReverseEffect() { 
	int i = targetEnemy->GetStatus()->GetHP();
	battleManager_->HealEnemy(value, targetEnemy, playerStatus_);
	i -= targetEnemy->GetStatus()->GetHP();

	if (i < 0) {
		battleManager_->DamagePlayer(-i, playerStatus_);
	}

	return true;
}
