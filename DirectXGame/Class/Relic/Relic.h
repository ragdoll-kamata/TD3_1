#pragma once
#include <KamataEngine.h>

using namespace KamataEngine;

#include "RelicEffectTiming.h"
#include "Status.h"
#include "NumberSprite.h"

class CardManager;
class BattleManager;

class Relic {
public:
	virtual ~Relic() = default;
	/// <summary>
	/// レリック初期化
	/// </summary>
	void Initialize(CardManager* cardManager, BattleManager* battleManager);
	/// <summary>
	/// レリック更新
	/// </summary>
	void Update();
	/// <summary>
	/// レリック描画
	/// </summary>
	void Draw();

	
	void Effect(RelicEffectTiming effectTiming);

	void SetPos(Vector2 pos);

	void SetPlayerStatus(Status* player) { playerStatus_ = player; }

protected:
	virtual void PeculiarInitialize() = 0;

	virtual void ApplyEffect() = 0;

protected:
	CardManager* cardManager_ = nullptr;
	BattleManager* battleManager_ = nullptr;

	Status* playerStatus_ = nullptr;
	RelicEffectTiming effectTiming_;

	Sprite sprite;
	NumberSprite numberSprite;

	int stack_ = 0;
	bool isStack_ = false;
};
