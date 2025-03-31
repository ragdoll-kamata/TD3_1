#pragma once
#include <memory>
#include <KamataEngine.h>
#include "BattleManager.h"
#include "Status.h"
using namespace KamataEngine;
class Enemy;
class CardManager;

enum class CardType {
	Damage,
	Shield,
	Skill,
	Ability,
	StateAnomaly,
};
enum class CardRange {
	One,
	EnemyWhole,
	Whole,
	Random,
	Self,
	Card,
};
class Card {
public:
	virtual ~Card() = default;
	void Initialize();

protected:
	virtual void IndividualInitialize() = 0;
public:

	

	void SetSpritePos(const Vector2& pos) { sprite.SetPosition(pos); }
	Vector2 GetSpritePos() const { return sprite.GetPosition(); }

	void Updata();

	void Draw();

	virtual bool Effect() = 0;

	virtual bool ReverseEffect() = 0;

	virtual std::unique_ptr<Card> clone() const = 0;

	CardType GetCardType() { return cardType; }
	CardRange GetCardRange() { return cardRange; }

	bool GetIsReverse() const { return isReverse; }

	void SetIsReverse(bool is);

	int GetId() const { return id; }

	int GetLuck() const { 
		if (!isReverse) {
			return luck;
		} else {
			return rverseLuck;
		}
	}

	void SetTargetEnemy(Enemy* enemy) { targetEnemy = enemy; }

	bool IsOnCollision(Vector2 pos);


	void SetCardManager(CardManager* cardManager) { cardManager_ = cardManager; }
	void SetBattleManager(BattleManager* battleManager) { battleManager_ = battleManager; }
	void SetPlayerStatus(Status* status) { playrStatus_ = status; }


	void SetSize(float size) { size_ = size; }

protected:
	Enemy* targetEnemy = nullptr;

	Status* playrStatus_ = nullptr;

	CardManager* cardManager_ = nullptr;
	BattleManager* battleManager_ = nullptr;

	Sprite sprite;
	uint32_t TH;
	float size_ = 1.0f;

	float rotate = 0.0f;
	float nextRotate = 0.0f;

	int value;
	bool isReverse;
	bool prevIsReverse;
	int luck;
	int rverseLuck;
	CardType cardType;
	CardRange cardRange;
	int id;
};
