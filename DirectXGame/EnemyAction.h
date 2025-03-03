#pragma once

enum class Debuff {
	Poison,

};

class Player;
class EnemyAction {
public:

	virtual ~EnemyAction() = default;

	void Initialize(int value, int value2 = 0);

	virtual void Execute() = 0; // 純粋仮想関数

	void SetPlayer(Player* player) { player_ = player; }
	
protected:
	Player* player_ = nullptr;

	int value_;
	int value2_;
};
