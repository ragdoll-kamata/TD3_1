#include "Enemy.h"
#include <algorithm>

void Enemy::Update() { 
	if (maxHP < HP) {
		HP = maxHP;
	}

	switch (enemyTurn) {
	case Enemy::EnemyTurn::Standby:
		break;
	case Enemy::EnemyTurn::Start:
		enemyTurn = EnemyTurn::Main;
		break;
	case Enemy::EnemyTurn::Main:
		if (!isReverse) {
			enemyAction[index]->Execute();
		} else {
			reverseEnemyAction[index]->Execute();
		}
		enemyTurn = EnemyTurn::End;
		break;
	case Enemy::EnemyTurn::End:
		index++;
		if (index >= enemyAction.size()) {
			index = 0;
		}
		enemyTurn = EnemyTurn::Standby;
		break;
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
