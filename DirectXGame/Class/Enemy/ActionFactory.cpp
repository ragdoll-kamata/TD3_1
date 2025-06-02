#include "ActionFactory.h"
#include "AtackAction.h"
#include "ShieldAction.h"
#include "ContinuousAttackAction.h"
#include "ContinuousHealAction.h"
#include "DebuffAtackAction.h"
#include "BuffAction.h"
#include "DebuffAction.h"
#include "DebuffShieldAction.h"
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
	if (enemyName == "DebuffAttack") {
		return std::make_unique<DebuffAtackAction>();
	}
	if (enemyName == "Debuff") {
		return std::make_unique<DebuffAction>();
	}
	if (enemyName == "DebuffShield") {
		return std::make_unique<DebuffShieldAction>();
	}

	return nullptr;
}
