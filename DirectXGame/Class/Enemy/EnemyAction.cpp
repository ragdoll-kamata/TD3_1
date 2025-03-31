#include "EnemyAction.h"

void EnemyAction::Initialize(Status* status, int value, int value2, Enemy* enemy) {
	status_ = status;
	value_ = value;
	value2_ = value2;
	enemy_ = enemy;
}