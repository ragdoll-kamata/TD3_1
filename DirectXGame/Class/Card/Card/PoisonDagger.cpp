#include "PoisonDagger.h"
#include "StatusEffectFactory.h"
#include "BattleManager.h"
void PoisonDagger::IndividualInitialize() {
	TH = TextureManager::GetInstance()->Load("card/PoisonDagger.png");
	sprite.SetTextureHandle(TH);
	luck = 0;
	reverseLuck = 0;
	//sprite.SetColor({0.5f, 0.0f, 0.5f, 1.0f});
	cardType = CardType::Damage;
	cardRange = CardRange::One;
	id = 13;
	value = 3;
}

bool PoisonDagger::Effect() {
	battleManager_->DamageEnemy(value, targetEnemy, playerStatus_);
	battleManager_->StatusEffectEnemy(targetEnemy, std::move(StatusEffectFactory::CreateStatusEffect("Poison")), 5);


	return true;
}

bool PoisonDagger::ReverseEffect() {
	battleManager_->DamageEnemy(-value, targetEnemy, playerStatus_);
	battleManager_->StatusEffectEnemy(targetEnemy, std::move(StatusEffectFactory::CreateStatusEffect("Regeneration")), 5);
	return true;
}