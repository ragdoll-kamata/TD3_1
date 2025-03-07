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

		enemyTurn = EnemyTurn::End;
		break;
	case Enemy::EnemyTurn::End:
		PredictNextAction();
		enemyTurn = EnemyTurn::Standby;
		break;
	}
	numberSprite.SetNumber(HP);
}

void Enemy::Draw() { 
	sprite.Draw();
	numberSprite.Draw();
}

bool Enemy::StartMainTurn() { return true; }

bool Enemy::MainTurn() { 
	if (!isReverse) {
		enemyAction->Execute();
	} else {
		reverseEnemyAction->Execute();
	}
	return true;
}

bool Enemy::EndMainTurn() { 
	PredictNextAction();
	return true;
}

void Enemy::StartBattle() {
	PredictNextAction();
	StartBattlePeculiar();
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
