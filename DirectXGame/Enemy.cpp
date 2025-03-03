#include "Enemy.h"
#include <algorithm>

void Enemy::Update() { 
	if (maxHP < HP) {
		HP = maxHP;
	}
	if (enemyTurn == EnemyTurn::End) {
		index++;
		if (index > enemyAction.size()) {
			index = 0;
		}
		enemyTurn = EnemyTurn::Standby;
	}
	numberSprite.SetNumber(HP);
}

void Enemy::StartEnemyTurn() {
	if (enemyTurn == EnemyTurn::Standby) {
		enemyTurn = EnemyTurn::Start;
	}
}

void Enemy::Draw() { 
	sprite.Draw();
	numberSprite.Draw();
}

bool Enemy::IsOnCollision(Vector2 pos) {
	Vector2 hPos{
	    std::clamp(pos.x, sprite.GetPosition().x - halfSize.x, sprite.GetPosition().x + halfSize.x),
	    std::clamp(pos.y, sprite.GetPosition().y - halfSize.y, sprite.GetPosition().y + halfSize.y),
	};

	hPos.x -= pos.x;
	hPos.y -= pos.y;
	float len = MathUtility::Length(hPos);
	if (len <= 0.0f) {
		return true;
	}
	return false;
}
