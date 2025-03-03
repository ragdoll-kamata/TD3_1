#pragma once
#include <memory>
#include <KamataEngine.h>

using namespace KamataEngine;
class Enemy;
class CardManager;
class Player;
enum class CardType {
	Damage,
	Shield,
	Skill,
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



	virtual void Initialize();

	void SetSpritePos(const Vector2& pos) { sprite.SetPosition(pos); }

	void Draw();

	virtual bool Effect() = 0;

	virtual bool ReverseEffect() = 0;

	virtual std::unique_ptr<Card> clone() const = 0;

	CardRange GetCardRange() { return cardRange; }

	bool GetIsReverse() const { return isReverse; }

	void SetIsReverse(bool is) { isReverse = is; }

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
	void SetPlayer(Player* player) { player_ = player; }

protected:
	Enemy* targetEnemy = nullptr;

	CardManager* cardManager_ = nullptr;
	Player* player_ = nullptr;

	Sprite sprite;
	uint32_t TH;


	int value;
	bool isReverse;
	int luck;
	int rverseLuck;
	CardType cardType;
	CardRange cardRange;
	int id;
};
