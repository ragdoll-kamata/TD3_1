#pragma once
#include "NumberSprite.h"
class Player {
public:
	void Initialize();

	void Update();

	void StartEnemyTurn();
	void Draw();

	void ClearShield();

	void AddShield(int v);

	void Damage(int damage);

private:
	NumberSprite numberSprite;
	NumberSprite numberSprite2;

	int MaxHP = 90;
	int HP;
	int shield;
};
