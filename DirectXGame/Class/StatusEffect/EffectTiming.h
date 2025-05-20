#pragma once
enum class EffectTiming {
	StartOfTurn,    // ターン開始時
	EndOfTurn,      // ターン終了時
	BeforeAttack,   // 攻撃前
	AfterAttack,    // 攻撃後
	BeforeDefense,  // 防御前
	BeforeHeal,     // 与回復前
	AfterHeal,      // 与回復後
	BeforeRecovery, // 被回復前
	BonusDamage,    // ボーナスダメージ
	BonusShield,    // ボーナスシールド
	OnDefense,      // 防御しきれた時
	OnDamage,       // ダメージを受けた時
	OnHeal,         // 回復した時
	OnDeath,        // 死亡時
	OnDraw,         // ドロー時
};