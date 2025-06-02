#include "DesperateAttack.h"
#include "StatusEffectFactory.h"
#include "BattleManager.h"

void DesperateAttack::IndividualInitialize() {
	TH = TextureManager::GetInstance()->Load("card/DesperateAttack.png");
	sprite.SetTextureHandle(TH);
	luck = 1;
	reverseLuck = 1;
	//sprite.SetColor({1.0f, 0.0f, 0.0f, 1.0f});
	cardType = CardType::Skill;
	cardRange = CardRange::Self;
	id = 104;
	value = 2;
}

bool DesperateAttack::Effect() {
	battleManager_->ShieldPlayer(-8, playerStatus_);
	battleManager_->StatusEffectPlayer(StatusEffectFactory::CreateStatusEffect("Strongening"), value);
	return true;
}

bool DesperateAttack::ReverseEffect() {
	battleManager_->ShieldPlayer(8, playerStatus_);
	battleManager_->StatusEffectPlayer(StatusEffectFactory::CreateStatusEffect("Weakening"), value);
	return true;
}
