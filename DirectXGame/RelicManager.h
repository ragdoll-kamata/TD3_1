#pragma once
#include <memory>
#include <vector>

#include "RelicEffectTiming.h"
#include "Relic.h"
class CardManager;
class BattleManager;
class RelicManager {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(CardManager* cardManager, BattleManager* battleManager);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void RelicEffect(RelicEffectTiming effectTiming);

private:
	CardManager* cardManager_ = nullptr;
	BattleManager* battleManager_ = nullptr;

	std::vector<std::unique_ptr<Relic>> relics;

	
};
