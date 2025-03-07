#include "BattleManager.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "CardManager.h"


void BattleManager::Initialize(Player* player, CardManager* cardManager, EnemyManager* enemyManager) {
	player_ = player;
	cardManager_ = cardManager;
	enemyManager_ = enemyManager;
}

void BattleManager::Update() {
	cardManager_->BattleUpdata();
	mBattlePhase[turn]();
}

void BattleManager::StartBattle() {
	enemyManager_->StartBattle();
	cardManager_->StartBattle();
}

void BattleManager::DamagePlayer(int num) {
	player_->Damage(num);
}

void BattleManager::ShieldPlayer(int num) { 
	player_->AddShield(num);
}

void BattleManager::DamageEnemy(int num, Enemy* enemy) { 
	enemy->DamageHP(num);
}

void BattleManager::PlayerStartMainTurn() { 
	if (cardManager_->StartMainTurn()) {
		turn = BattlePhase::PlayerMainTurn;
	}
	player_->ClearShield();
}

void BattleManager::PlayerMainTurn() { 
	if (cardManager_->MainTurn()) {
		turn = BattlePhase::PlayerEndMainTurn;
	}
}

void BattleManager::PlayerEndMainTurn() { 
	if (cardManager_->EndMainTurn()) {
		turn = BattlePhase::EnemyStartMainTurn;
	}
}

void BattleManager::EnemyStartMainTurn() {
	if (enemyManager_->StartMainTurn()) {
		turn = BattlePhase::EnemyMainTurn;
	}
}

void BattleManager::EnemyMainTurn() {
	if (enemyManager_->MainTurn()) {
		turn = BattlePhase::EnemyEndMainTurn;
	}

}

void BattleManager::EnemyEndMainTurn() {
	if (enemyManager_->EndMainTurn()) {
		turn = BattlePhase::PlayerStartMainTurn;
	}
}
