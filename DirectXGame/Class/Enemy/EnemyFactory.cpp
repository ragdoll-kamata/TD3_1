#include "EnemyFactory.h"
#include "Dummy.h"
#include "Caterpillar.h"
#include "PsychoAxe.h"
std::unique_ptr<Enemy> EnemyFactory::CreateEnemy(std::string enemyname) {

	if (enemyname == "dummy") {
		return std::make_unique<Dummy>();
	}
	if (enemyname == "PsychoAxe") {
		return std::make_unique<PsychoAxe>();
	}
	if (enemyname == "Caterpillar") {
		return std::make_unique<Caterpillar>();
	}
	return nullptr;
}
