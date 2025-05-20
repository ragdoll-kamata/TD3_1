#pragma once
#include <KamataEngine.h>

using namespace KamataEngine;
class HPGauge {
public:
	void Initialize(Vector2 pos, int maxHP);

	void Update();

	void Draw();

	void SetHP(int hp) { HP_ = hp; }

private:

	int HP_ = 0;
	int maxHP_ = 0;
	Sprite sprite;
	Sprite sprite2;

};
