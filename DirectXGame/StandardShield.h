#pragma once
#include "Card.h"
class StandardShield : public Card {
public:
	void Initialize() override;

	void Effect() override;

	void ReverseEffect() override;

	std::unique_ptr<Card> clone() const override {
		return std::make_unique<StandardShield>(*this); // 自分のコピーを作成
	}

private:
};
