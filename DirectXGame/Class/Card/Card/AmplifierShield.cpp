#include "AmplifierShield.h"
#include "BattleManager.h"
void AmplifierShield::IndividualInitialize() {
	TH = TextureManager::GetInstance()->Load("card/AmplifireShield.png");
	sprite.SetTextureHandle(TH);
	luck = 1;
	reverseLuck = -1;
	//sprite.SetColor({0.5f, 0.5f, 0.5f, 1.0f});
	cardType = CardType::Shield;
	cardRange = CardRange::Self;
	id = 100;
	value = 25;
}

bool AmplifierShield::Effect() {
	battleManager_->DamagePlayer(value / 5, playerStatus_);
	battleManager_->ShieldPlayer(value, playerStatus_);

	return true;
}

bool AmplifierShield::ReverseEffect() {
	battleManager_->HealPlayer(value / 5, playerStatus_);
	battleManager_->ShieldPlayer(-value, playerStatus_);

	return true;
}
