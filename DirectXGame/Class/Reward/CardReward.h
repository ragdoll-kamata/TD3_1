#pragma once
#include "Reward.h"
#include <memory>
#include <vector>
#include "Card.h"
#include "Button.h"
class CardReward : public Reward {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(CardManager* cardManager, RelicManager* relicManager) override;

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update() override;

	/// <summary>
	/// 描画
	/// </summary>
	void CardDraw() override;

private:
	std::vector<std::unique_ptr<Card>> reward;
	CardManager* cardManager_ = nullptr;
	Button button;
};
