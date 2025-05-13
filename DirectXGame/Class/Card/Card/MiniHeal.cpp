#include "MiniHeal.h"
#include "BattleManager.h"
void MiniHeal::IndividualInitialize() { 
	luck = 1;
	reverseLuck = -1;
	sprite.SetColor({0.5f, 1.0f, 0.0f, 1.0f});
	cardType = CardType::Skill;
	cardRange = CardRange::Self;
	id = 6;
	value = 1001;
}

bool MiniHeal::Effect() { 
	battleManager_->HealPlayer(value, playrStatus_);
	return true;
}

bool MiniHeal::ReverseEffect() {
	battleManager_->DamagePlayer(value, playrStatus_);
	return true;
}
