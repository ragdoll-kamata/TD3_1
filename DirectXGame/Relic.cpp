#include "Relic.h"
using namespace MathUtility;
void Relic::Initialize(CardManager* cardManager, BattleManager* battleManager) {
	cardManager_ = cardManager;
	battleManager_ = battleManager;
	sprite.Initialize();
	sprite.SetColor({1.0f, 1.0f, 1.0f, 1.0f});
	sprite.SetSize({45.0f, 45.0f});
	sprite.SetAnchorPoint({0.0f, 0.0f});

	numberSprite.Initialize({}, 0.4f, {1.0f, 1.0f});

	PeculiarInitialize();
}

void Relic::Update() {
	if (isStack_) {
		numberSprite.SetNumber(stack_);
	}
}

void Relic::Draw() {
	sprite.Draw();
	if (isStack_) {
		numberSprite.Draw();
	}
}

void Relic::Effect(RelicEffectTiming effectTiming) {
	if (effectTiming_ == effectTiming) {
		ApplyEffect();
	}
}

void Relic::SetPos(Vector2 pos) {
	sprite.SetPosition(pos);
	numberSprite.SetPosition(pos + Vector2(45.0f, 45.0f));
}
