#pragma once
#include "Event.h"
#include <vector>
#include "Button.h"
class RestEvent : public Event {
public:
// Event を介して継承されました
	void Initialize(RewardManager* rewardManager) override;
	void Update() override;
	void Draw() override;

private:
	std::unique_ptr<Button> restButton;
	std::unique_ptr<Button> disCardButton;
	std::unique_ptr<Button> disCardCancelButton;
	bool is = false;

	float prevWheel = 0.0f;
	float scroll = 0.0f;
	std::vector<Card*> sCard;
	std::vector<Vector2> sPos;
	Sprite back;
	int heal = 0;
};
