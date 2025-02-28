#include "EnemyManager.h"
#include "Dummy.h"
void EnemyManager::Initialize() {

	enemy.push_back(std::make_unique<Dummy>());
	enemy[0]->Initialize();
}

void EnemyManager::Update() {}

void EnemyManager::Draw() {
	for (int i = 0; i < enemy.size(); i++) {
		enemy[i]->Draw();
	}
}

uint32_t EnemyManager::IsOnCollision(Vector2 pos) {
	for (int i = 0; i < enemy.size(); i++) {
		if (enemy[i]->IsOnCollision(pos)) {
			return i + 1;
		}
	}
	return 0;
}

Enemy* EnemyManager::GetEnemy(const uint32_t& EH) { 
	if (enemy.size() >= EH && EH > 0) {
		return enemy[EH - 1].get();
	}
	return nullptr;
}
