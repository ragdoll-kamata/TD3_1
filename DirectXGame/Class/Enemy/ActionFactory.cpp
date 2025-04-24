#include "ActionFactory.h"
#include "AtackAction.h"
#include "ShieldAction.h"
#include "ContinuousAttackAction.h"
#include "ContinuousHealAction.h"
#include "BuffAction.h"
std::unique_ptr<EnemyAction> ActionFactory::CreateAction(std::string enemyName) {
	
	if (enemyName == "Atack") {
		return std::make_unique<AtackAction>();
	}
	if (enemyName == "Shield") {
		return std::make_unique<ShieldAction>();
	}
	if (enemyName == "ContinuousAttack") {
		return std::make_unique<ContinuousAttackAction>();
	}
	if( enemyName == "ContinuousHeal") {
		return std::make_unique<ContinuousHealAction>();
	}
	if (enemyName == "Buff") {
		return std::make_unique<BuffAction>();
	}
	
	return nullptr;
}
