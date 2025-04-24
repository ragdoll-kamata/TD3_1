#pragma once
#include "Card.h"
class ClusterGrenade : public Card {
public:
	void IndividualInitialize() override;
	bool Effect() override;
	bool ReverseEffect() override;
	std::unique_ptr<Card> clone() const override {
		return std::make_unique<ClusterGrenade>(*this); // 自分のコピーを作成
	}
};
