#include "Enemy.h"
#include <algorithm>

void Enemy::Update() { 
	status_->Update();
}

void Enemy::Draw() { 
	sprite.Draw();
	status_->Draw();
}

bool Enemy::StartMainTurn() { 
	status_->ClearShield();
	return true;
}

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

void Enemy::AddStatusEffect(std::unique_ptr<StatusEffect> statusEffect, int stack) {
	status_->AddStatusEffect(std::move(statusEffect), stack);
}

void Enemy::Effect(EffectTiming effectTiming, StackDecreaseTiming stackDecreaseTiming) { 
	status_->Effect(effectTiming, stackDecreaseTiming);
}
