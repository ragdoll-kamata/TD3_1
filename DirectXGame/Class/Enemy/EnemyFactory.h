#pragma once
#include <memory>
#include <string>
class Enemy;
class EnemyFactory {
public:
	std::unique_ptr<Enemy> CreateEnemy(std::string enemyname);

};
