#include "BattleManager.h"
#include "Player.h"
#include "Enemy.h"
#include "EnemyManager.h"
#include "CardManager.h"
#include "StatusEffect.h"
#include "RewardManager.h"
#include "MapManager.h"

void BattleManager::Initialize(Player* player, CardManager* cardManager, EnemyManager* enemyManager) {
	player_ = player;
	cardManager_ = cardManager;
	enemyManager_ = enemyManager;
	isEnd = true;
	turn = BattlePhase::StandbyTurn;
}

void BattleManager::Update() {
	if (!mapManager_->GetIsMapOpen()) {
		
		mBattlePhase[turn]();
		cardManager_->BattleUpdata();
		player_->Update();
		if (enemyManager_->GetEnemyCount() <= 0) {
			if (!isEnd) {
				EndBattle();
			}
		}
	}
}

void BattleManager::Draw() {
	enemyManager_->Draw();

	player_->Draw();

	cardManager_->DrawBattle();
}

void BattleManager::StartBattle(BattleEnemyType battleEnemyType) {
	enemyManager_->StartBattle(battleEnemyType);
	cardManager_->StartBattle();
	mapManager_->SetIsMove(false);
	isEnd = false;
	turn = BattlePhase::StartBattleTurn;
	battleEnemyType_ = battleEnemyType;
}

void BattleManager::EndBattle() {
	player_->EndBattle();
	
	isEnd = true;
	turn = BattlePhase::EndBattleTurn;

}

void BattleManager::DamagePlayer(int num, Status* status) {
	player_->GetStatus()->Damage(num, status);
}

void BattleManager::HealPlayer(int num, Status* status) {
	player_->GetStatus()->Heal(num, status);
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

void BattleManager::HealEnemy(int num, Enemy* enmey, Status* status) { 
	enmey->GetStatus()->Heal(num, status);
}

void BattleManager::ShieldEnemy(int num, Enemy* enmey, Status* status) { 
	enmey->GetStatus()->AddShield(num, status); }

void BattleManager::StatusEffectEnemy(Enemy* enemy, std::unique_ptr<StatusEffect> statusEffect, int stack) {
	enemy->AddStatusEffect(std::move(statusEffect), stack);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void BattleManager::StartBattleTurn() {
	if (cardManager_->StartBattleTrue()) {
		turn = BattlePhase::PlayerStartMainTurn;
	}
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
		if (cardManager_->EndBattleTrue()) {
			rewardManager_->CreateBattleReward(battleEnemyType_);
		}
	} else {
		if (rewardManager_->IsSkip()) {
			mapManager_->SetIsMapOpen(true);
			mapManager_->SetIsMove(true);
			turn = BattlePhase::StandbyTurn;
		}
	}
}


void BattleManager::StandbyTurn() {}
