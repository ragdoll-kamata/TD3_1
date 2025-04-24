#pragma once
#include <memory>
#include <vector>

#include "RelicEffectTiming.h"
#include "Relic.h"
#include "RelicFactory.h"
class CardManager;
class BattleManager;
class Player;
class RelicManager {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(CardManager* cardManager, BattleManager* battleManager, Player* player);
	/// <summary>
	/// 更新
	/// </summary>
	void Update();
	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void RelicEffect(RelicEffectTiming effectTiming);

	void AddRelic(std::unique_ptr<Relic> relic) { relics.push_back(std::move(relic)); }

	std::unique_ptr<Relic> CreateRandomRelic();

private:
	CardManager* cardManager_ = nullptr;
	BattleManager* battleManager_ = nullptr;
	Player* player_ = nullptr;
	std::unique_ptr<RelicFactory> relicFactory_;

	std::vector<std::unique_ptr<Relic>> relics;

	int rareProbability = 0;
	const int rareMinProbability = 5;

	int unCommonProbability = 0;
	const int unCommonMinProbability = 10;
};
