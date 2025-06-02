#pragma once
#include <unordered_map>
#include <memory>
#include <functional>
#include "StatusEffect.h"
#include "BattleEnemyType.h"

class EnemyManager;
class CardManager;
class RewardManager;
class MapManager;
class Player;
class Enemy;

class BattleManager {
public:
	enum class BattlePhase {
		StartBattleTurn,
		PlayerStartMainTurn,
		PlayerMainTurn,
		PlayerEndMainTurn,
		EnemyStartMainTurn,
		EnemyMainTurn,
		EnemyEndMainTurn,
		EndBattleTurn,
		StandbyTurn,
	};
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Player* player, CardManager* cardManager, EnemyManager* enemyManager);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();


	void Draw();

	void SetRewardManager(RewardManager* rewardManager) { rewardManager_ = rewardManager; }
	void SetMapManager(MapManager* mapManager) { mapManager_ = mapManager; }

	void StartBattle(BattleEnemyType battleEnemyType);

	void EndBattle();

	void DamagePlayer(int num, Status* status);

	void HealPlayer(int num, Status* status);

	void ShieldPlayer(int num, Status* status);

	void StatusEffectPlayer(std::unique_ptr<StatusEffect> statusEffect, int stack);

	void DamageEnemy(int num, Enemy* enmey, Status* status);

	void HealEnemy(int num, Enemy* enmey, Status* status);

	void ShieldEnemy(int num, Enemy* enmey, Status* status);

	void StatusEffectEnemy(Enemy* enemy, std::unique_ptr<StatusEffect> statusEffect, int stack);


private:
	void StartBattleTurn();

	void PlayerStartMainTurn();
	void PlayerMainTurn();
	void PlayerEndMainTurn();
	void EnemyStartMainTurn();
	void EnemyMainTurn();
	void EnemyEndMainTurn();

	void EndBattleTurn();


	void RewardTurn();

	void StandbyTurn();

private:
	BattlePhase turn = BattlePhase::PlayerStartMainTurn;
	BattleEnemyType battleEnemyType_;

	std::unordered_map<BattlePhase, std::function<void()>> mBattlePhase{
	    {BattlePhase::StartBattleTurn,     [this]() { StartBattleTurn(); }    },
	    {BattlePhase::PlayerStartMainTurn, [this]() { PlayerStartMainTurn(); }},
	    {BattlePhase::PlayerMainTurn,      [this]() { PlayerMainTurn(); }     },
	    {BattlePhase::PlayerEndMainTurn,   [this]() { PlayerEndMainTurn(); }  },
	    {BattlePhase::EnemyStartMainTurn,  [this]() { EnemyStartMainTurn(); } },
	    {BattlePhase::EnemyMainTurn,       [this]() { EnemyMainTurn(); }      },
	    {BattlePhase::EnemyEndMainTurn,    [this]() { EnemyEndMainTurn(); }   },
	    {BattlePhase::EndBattleTurn,       [this]() { EndBattleTurn(); }      },
	    {BattlePhase::StandbyTurn,         [this]() { StandbyTurn(); }        },
	};

	Player* player_ = nullptr;
	CardManager* cardManager_ = nullptr;
	EnemyManager* enemyManager_ = nullptr;
	RewardManager* rewardManager_ = nullptr;
	MapManager* mapManager_ = nullptr;

	bool isEnd = false;


	bool isPlayerStart = false;
};
