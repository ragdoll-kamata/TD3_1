#pragma once
#include <vector>
#include <functional>
#include <KamataEngine.h>
using namespace KamataEngine;
class Enemy {
public:
	virtual ~Enemy() = default;
	enum class BehavioralPattern {
		Atack,
		Shield,
		Debuff,
		Buff,
		DebuffAtack,
		BuffShield,
	};

	virtual void Initialize() = 0;

	void Update();

	void Draw();

	bool IsOnCollision(Vector2 pos);

protected:
	Sprite sprite;
	uint32_t TH;

	Vector2 pos_;
	Vector2 halfSize;

	std::vector<std::function<void()>> fBehavioralPattern;
	int index = 0;
	int value;
	int HP;
	BehavioralPattern behavioralPattern_;
};
