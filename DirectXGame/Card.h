#pragma once
#include <memory>
#include <KamataEngine.h>

using namespace KamataEngine;

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
};
class Card {
public:
	virtual ~Card() = default;



	virtual void Initialize();

	void SetSpritePos(const Vector2& pos) { sprite.SetPosition(pos); }

	void Draw();

	virtual void Effect() = 0;

	virtual void ReverseEffect() = 0;

	virtual std::unique_ptr<Card> clone() const = 0;

	bool GetIsReverse() const { return isReverse; }

	void SetIsReverse(bool is) { isReverse = is; }

	int GetLuck() const { 
		if (!isReverse) {
			return luck;
		} else {
			return rverseLuck;
		}
	}

protected:
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
