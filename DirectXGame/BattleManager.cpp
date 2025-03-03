#include "BattleManager.h"

BattleManager* BattleManager::instance = nullptr;

void BattleManager::Initialize() {}

void BattleManager::Update() {






}

BattleManager* BattleManager::GetInstance() {
	if (!instance) {
		instance = new BattleManager;
		instance->Initialize();
	}
	
	return instance;
}
