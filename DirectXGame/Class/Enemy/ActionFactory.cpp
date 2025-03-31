#include "ActionFactory.h"
#include "AtackAction.h"
#include "ShieldAction.h"
std::unique_ptr<EnemyAction> ActionFactory::CreateAction(std::string enemyname) {
	
	if (enemyname == "Atack") {
		return std::make_unique<AtackAction>();
	}
	if (enemyname == "Shield") {
		return std::make_unique<ShieldAction>();
	}
	
	return nullptr;
}
