#pragma once
#include "Card.h"
class DrawCard : public Card {

	void IndividualInitialize() override;

	bool Effect() override;

	bool ReverseEffect() override;

	std::unique_ptr<Card> clone() const override {
		return std::make_unique<DrawCard>(*this); // 自分のコピーを作成
	}

private:
};
