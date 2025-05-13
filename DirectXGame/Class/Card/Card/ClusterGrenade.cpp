#include "ClusterGrenade.h"
#include "BattleManager.h"
void ClusterGrenade::IndividualInitialize() {
	luck = 0;
	reverseLuck = -3;
	sprite.SetColor({1.0f, 0.2f, 0.0f, 1.0f});
	cardType = CardType::Damage;
	cardRange = CardRange::One;
	id = 11;
}

bool ClusterGrenade::Effect() {
	for (int i = 0; i < 4; i++) {
		battleManager_->DamageEnemy(3, targetEnemy, playrStatus_);
	}
	battleManager_->DamagePlayer(3, playrStatus_);
	return true;
}

bool ClusterGrenade::ReverseEffect() { 
	for (int i = 0; i < 5; i++) {
		battleManager_->DamagePlayer(3, playrStatus_);
	}
	battleManager_->DamageEnemy(3, targetEnemy, playrStatus_);
	return true;
}
