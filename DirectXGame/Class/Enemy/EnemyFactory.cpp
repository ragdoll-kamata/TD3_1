#include "EnemyFactory.h"
#include "Dummy.h"
std::unique_ptr<Enemy> EnemyFactory::CreateEnemy(std::string enemyname) {

	if (enemyname == "dummy") {
		return std::make_unique<Dummy>();
	}
	return nullptr;
}
