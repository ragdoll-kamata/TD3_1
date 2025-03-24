#include "BattleManager.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "CardManager.h"
#include "StatusEffect.h"
#include "RewardManager.h"

void BattleManager::Initialize(Player* player, CardManager* cardManager, EnemyManager* enemyManager) {
	player_ = player;
	cardManager_ = cardManager;
	enemyManager_ = enemyManager;
}

void BattleManager::Update() {
	cardManager_->BattleUpdata();
	enemyManager_->Update();
	player_->Update();
	mBattlePhase[turn]();
	if (enemyManager_->GetEnemyCount() <= 0) {
		if (!isReward) {
			EndBattle();
		}
	}
}

void BattleManager::Draw() {
	enemyManager_->Draw();

	player_->Draw();

	cardManager_->DrawBattle();
	if (turn == BattlePhase::EndBattleTurn) {
		//cardManager_->DrawReward();
	}
}

void BattleManager::StartBattle() {
	enemyManager_->StartBattle();
	cardManager_->StartBattle();
	isReward = false;
	turn = BattlePhase::EnemyEndMainTurn;
}

void BattleManager::EndBattle() {
	cardManager_->EndBattle();
	player_->EndBattle();
	
	rewardManager_->CreateBattleReward();

	isReward = true;
	turn = BattlePhase::EndBattleTurn;

}

void BattleManager::DamagePlayer(int num, Status* status) {
	player_->GetStatus()->Damage(num, status);
}

void BattleManager::ShieldPlayer(int num, Status* status) { 
	player_->GetStatus()->AddShield(num, status);
}

void BattleManager::StatusEffectPlayer(std::unique_ptr<StatusEffect> statusEffect, int stack) {
	player_->GetStatus()->AddStatusEffect(std::move(statusEffect), stack);
}

void BattleManager::DamageEnemy(int num, Enemy* enemy, Status* status) { 
	enemy->GetStatus()->Damage(num, status); 
}

void BattleManager::ShieldEnemy(int num, Enemy* enmey, Status* status) { 
	enmey->GetStatus()->AddShield(num, status); }

void BattleManager::StatusEffectEnemy(Enemy* enemy, std::unique_ptr<StatusEffect> statusEffect, int stack) {
	enemy->AddStatusEffect(std::move(statusEffect), stack);
}

void BattleManager::PlayerStartMainTurn() { 
	if (cardManager_->StartMainTurn()) {
		turn = BattlePhase::PlayerMainTurn;
	}
	player_->GetStatus()->ClearShield();
	player_->GetStatus()->Effect(EffectTiming::StartOfTurn, StackDecreaseTiming::StartOfTurn);
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
	player_->GetStatus()->Effect(EffectTiming::EndOfTurn, StackDecreaseTiming::EndOfTurn);
}

void BattleManager::EnemyStartMainTurn() {
	if (enemyManager_->StartMainTurn()) {
		turn = BattlePhase::EnemyMainTurn;
	}
	enemyManager_->Effect(EffectTiming::StartOfTurn, StackDecreaseTiming::StartOfTurn);
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
	enemyManager_->Effect(EffectTiming::EndOfTurn, StackDecreaseTiming::EndOfTurn);
}

void BattleManager::EndBattleTurn() {
	
	if (!rewardManager_->IsReward()) {
		StartBattle();
	}

}
