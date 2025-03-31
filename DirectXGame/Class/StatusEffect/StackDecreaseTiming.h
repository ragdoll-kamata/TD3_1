#pragma once

enum class StackDecreaseTiming {
	NotDecrease, // 減少しない
	OnEffect,    // 効果発動時
	StartOfTurn, // ターン開始時
	EndOfTurn,   // ターン終了時
	OnAttack,    // 攻撃時
	OnDefense,   // 防御時
	OnDamage,    // ダメージを受けた時
	OnHeal,      // 回復した時
	None,        // なし
};