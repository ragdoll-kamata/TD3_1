#pragma once
#include <memory>
#include <KamataEngine.h>

using namespace KamataEngine;
class Card {
public:
	virtual ~Card() = default;
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


	virtual void Initialize();

	void SetSpritePos(const Vector2& pos) { sprite.SetPosition(pos); }

	void Draw();

	virtual void Effect() = 0;

	virtual void ReverseEffect() = 0;

	virtual std::unique_ptr<Card> clone() const = 0;

	bool GetIsReverse() const { return isReverse; }

	int GetLuck() const { return luck; }

private:
	Sprite sprite;
	uint32_t TH;


	int value;
	bool isReverse;
	int luck;
	CardType cardType;
	CardRange cardRange;
};
