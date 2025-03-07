#pragma once
#include <unordered_map>
#include <functional>

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

	void DamagePlayer(int num);

	void ShieldPlayer(int num);

	void InflictsAbnormalityPlayer();

	void DamageEnemy(int num, Enemy* enmey);

	void ShieldEnemy(int num, Enemy* enmey);

	void InflictsAbnormalityEnemy(Enemy* enemy);

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
