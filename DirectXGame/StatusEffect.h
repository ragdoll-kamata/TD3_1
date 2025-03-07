#pragma once

class BattleManager;
class Enemy;
enum class EffectTiming {
	StartOfTurn,   // ターン開始時
	EndOfTurn,     // ターン終了時
	BeforeAttack,  // 攻撃前
	AfterAttack,   // 攻撃後
	BeforeDefense, // 防御前
	AfterDefense,  // 防御後
	OnDamage,      // ダメージを受けた時
	OnHeal,        // 回復した時
	OnDeath        // 死亡時
};

enum class StackDecreaseTiming {
	OnEffect,    // 効果発動時
	StartOfTurn, // ターン開始時
	EndOfTurn,   // ターン終了時
	OnAttack,    // 攻撃時
	OnDefense,   // 防御時
	OnDamage,    // ダメージを受けた時
	OnHeal,      // 回復した時
	OnDeath      // 死亡時
};


class StatusEffect {
public:

	void Initialize(int stack, Enemy* enemy = nullptr) {
		stack_ = stack;
		enemy_ = enemy;
		PeculiarInitialize();
	}

	virtual void PeculiarInitialize() = 0;

	void Effect(EffectTiming effectTiming);

	virtual void ApplyEffect() = 0;

	void DecreaseStack(StackDecreaseTiming timing);
	void SetBattleManager(BattleManager* battleManager) { battleManager_ = battleManager; }


	void AddStack(int stack) { stack_ += stack; }

protected:
	int stack_;
	BattleManager* battleManager_;
	Enemy* enemy_;
	EffectTiming effectTiming_;
	StackDecreaseTiming stackDecreaseTiming_;
};
