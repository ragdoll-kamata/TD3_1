#pragma once
enum class RelicEffectTiming {
	Acquisition,    // 獲得時
	StartOfBattle,  // 戦闘開始時
	EndOfBattle,    // 戦闘終了時
	StartOfTurn,    // ターン開始時
	EndOfTurn,      // ターン終了時
	BeforeAttack,   // 攻撃前
	AfterAttack,    // 攻撃後
	BeforeDefense,  // 防御前
	BeforeHeal,     // 与回復前
	AfterHeal,      // 与回復後
	BeforeRecovery, // 被回復前
	OnDefense,      // 防御しきれた時
	OnDamage,       // ダメージを受けた時
	OnHeal,         // 回復した時
	OnDeath,        // 死亡時
	Draw,           // カードを引いた時
	Play,           // カードをプレイした時
	HandDeath,      // 手札を捨てた時
	DeckShuffle,    // デッキをシャッフルした時
	None,           // 効果なし
};