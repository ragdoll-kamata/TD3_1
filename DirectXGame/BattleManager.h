#pragma once
#include <unordered_map>
#include <memory>
#include <functional>
#include "StatusEffect.h"

class EnemyManager;
class CardManager;
class Player;
class Enemy;

class BattleManager {
public:
	enum class BattlePhase {
		PlayerStartMainTurn,
		PlayerMainTurn,
		PlayerEndMainTurn,
		EnemyStartMainTurn,
		EnemyMainTurn,
		EnemyEndMainTurn,
	};
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Player* player, CardManager* cardManager, EnemyManager* enemyManager);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();


	void StartBattle();

	void EndBattle();

	void DamagePlayer(int num, Status* status);

	void ShieldPlayer(int num, Status* status);

	void StatusEffectPlayer(std::unique_ptr<StatusEffect> statusEffect, int stack);

	void DamageEnemy(int num, Enemy* enmey, Status* status);

	void ShieldEnemy(int num, Enemy* enmey, Status* status);

	void StatusEffectEnemy(Enemy* enemy, std::unique_ptr<StatusEffect> statusEffect, int stack);


private:
	void PlayerStartMainTurn();
	void PlayerMainTurn();
	void PlayerEndMainTurn();
	void EnemyStartMainTurn();
	void EnemyMainTurn();
	void EnemyEndMainTurn();

private:
	BattlePhase turn = BattlePhase::PlayerStartMainTurn;

	std::unordered_map<BattlePhase, std::function<void()>> mBattlePhase{
	    {BattlePhase::PlayerStartMainTurn, [this]() { PlayerStartMainTurn(); }},
	    {BattlePhase::PlayerMainTurn,      [this]() { PlayerMainTurn(); }     },
	    {BattlePhase::PlayerEndMainTurn,   [this]() { PlayerEndMainTurn(); }  },
	    {BattlePhase::EnemyStartMainTurn,  [this]() { EnemyStartMainTurn(); } },
	    {BattlePhase::EnemyMainTurn,       [this]() { EnemyMainTurn(); }      },
	    {BattlePhase::EnemyEndMainTurn,    [this]() { EnemyEndMainTurn(); }   },
	};

	Player* player_ = nullptr;
	CardManager* cardManager_ = nullptr;
	EnemyManager* enemyManager_ = nullptr;

};
