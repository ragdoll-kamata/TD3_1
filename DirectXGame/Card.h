#pragma once
class Card {
public:
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

	virtual void Effect() = 0;

	virtual void ReverseEffect() = 0;

	virtual std::unique_ptr<Card> clone() const {
		return std::make_unique<Card>(*this); // 自分のコピーを作成
	}

	bool GetIsReverse() const { return isReverse; }

	int GetLuck() const { return luck; }

private:

	int value;
	bool isReverse;
	int luck;
	CardType cardType;
	CardRange cardRange;
};
