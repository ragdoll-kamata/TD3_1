#include "Player.h"
#include "StatusEffect.h"
void Player::Initialize() {
	status_ = std::make_unique<Status>();
	status_->Initialize({300.0f, 360.f}, {}, 90);
}

void Player::Update() {
	status_->Update();
}

void Player::Draw() {
	status_->Draw(); }

void Player::EndBattle() {
	status_->ClearStatusEffect();
}
