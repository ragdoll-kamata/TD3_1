#pragma once
#include "Card.h"
class DrawAttack : public Card {
	// Card を介して継承されました
	void IndividualInitialize() override;
	bool Effect() override;
	bool ReverseEffect() override;
	std::unique_ptr<Card> clone() const override {
		return std::make_unique<DrawAttack>(*this);
	}
};
