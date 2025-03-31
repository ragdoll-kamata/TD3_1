#pragma once
#include "Card.h"
class PoisonDagger : public Card {
	// Card を介して継承されました
	void IndividualInitialize() override;
	bool Effect() override;
	bool ReverseEffect() override;

	std::unique_ptr<Card> clone() const override {
		return std::make_unique<PoisonDagger>(*this); // 自分のコピーを作成
	}
};
