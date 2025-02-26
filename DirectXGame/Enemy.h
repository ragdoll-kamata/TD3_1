#pragma once
#include <vector>
#include <functional>
class Enemy {
public:
	enum class BehavioralPattern {
		Atack,
		Shield,
		Debuff,
		Buff,
		DebuffAtack,
		BuffShield,
	};

	void Update();

	void Draw();

protected:
	std::vector<std::function<void()>> fBehavioralPattern;
	int index = 0;
	int value;
	int HP;
	BehavioralPattern behavioralPattern_;
};
