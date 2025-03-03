#include "Player.h"

void Player::Initialize() {


	HP = MaxHP;
	numberSprite.Initialize({300.0f, 360.f}, 0.5f);
	numberSprite2.Initialize({300.0f, 400.f}, 0.5f);
}

void Player::Update() {
	numberSprite.SetNumber(HP);
	numberSprite2.SetNumber(shield);
}

void Player::Draw() {
	numberSprite.Draw();
	numberSprite2.Draw();
}

void Player::ClearShield() {
	shield=0;
}

void Player::AddShield(int v) {
	shield += v;
}

void Player::Damage(int damage) {
	if (shield > 0) {
		shield -= damage;
		HP -= shield;
	} else {
		HP -= damage;
	}



}
