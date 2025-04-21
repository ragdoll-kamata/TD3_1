#include "EnemyManager.h"
#include "Dummy.h"

void EnemyManager::Initialize() {

	enmeyFactory_ = std::make_unique<EnemyFactory>();
	std::random_device rd; // 乱数の種
	g.seed(rd());

}

void EnemyManager::Update() {

	for (int i = 0; i < enemy.size(); i++) {
		enemy[i]->Update();
		if (enemy[i]->IsDeath()) {
			enemy[i].reset();
			enemy.erase(enemy.begin() + i);
		}
	}
}

void EnemyManager::Draw() {
	for (int i = 0; i < enemy.size(); i++) {
		enemy[i]->Draw();
	}
}

bool EnemyManager::StartMainTurn() {
	for (int i = 0; i < enemy.size(); i++) {
		enemy[i]->StartMainTurn();
	}
	return true;
}

bool EnemyManager::MainTurn() {
	for (int i = 0; i < enemy.size(); i++) {
		enemy[i]->MainTurn();
	}
	return true;
}

bool EnemyManager::EndMainTurn() {
	for (int i = 0; i < enemy.size(); i++) {
		enemy[i]->EndMainTurn();
	}
	return true;
}

void EnemyManager::StartBattle(BattleEnemyType battleEnemyType) {
	CreateEnemy(battleEnemyType);
	for (int i = 0; i < enemy.size(); i++) {
		enemy[i]->StartBattle();
	}
}

void EnemyManager::CreateEnemy(BattleEnemyType battleEnemyType) {
	fCreateEnemy[battleEnemyType]();

}

uint32_t EnemyManager::IsOnCollision(Vector2 pos) {
	for (int i = 0; i < enemy.size(); i++) {
		if (enemy[i]->IsOnCollision(pos)) {
			return i + 1;
		}
	}
	return 0;
}

uint32_t EnemyManager::GetRadomEnemy() { 
	std::uniform_int_distribution<int> get_rand_uni_int(1, static_cast<int>(enemy.size()));
	return get_rand_uni_int(g);
}

Enemy* EnemyManager::GetEnemy(const uint32_t& EH) { 
	if (enemy.size() >= EH && EH > 0) {
		return enemy[EH - 1].get();
	}
	return nullptr;
}

void EnemyManager::Effect(EffectTiming effectTiming, StackDecreaseTiming stackDecreaseTiming) {
	for (int i = 0; i < enemy.size(); i++) {
		enemy[i]->Effect(effectTiming, stackDecreaseTiming);
	}
}

void EnemyManager::CreateNormalEnemy() {
	std::unique_ptr<Enemy> e = std::move(enmeyFactory_->CreateEnemy("dummy"));
	e->Initialize();

	e->SetBattleManager(battleManager_);

	enemy.push_back(std::move(e));
}

void EnemyManager::CreateEliteEnemy() {}

void EnemyManager::CreateBossEnemy() {}
