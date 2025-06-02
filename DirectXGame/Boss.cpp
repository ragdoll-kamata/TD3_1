#include "Boss.h"
#include "ActionFactory.h"
using namespace MathUtility;
void Boss::Initialize() {
	Enemy::Initialize();
	TH = TextureManager::GetInstance()->Load("white1x1.png");
	sprite.Initialize();
	sprite.SetTextureHandle(TH);
	sprite.SetAnchorPoint({0.5f, 0.5f});
	sprite.SetSize({200.0f, 200.0f});
	sprite.SetColor({
	    0.0f,
	    0.0f,
	    0.0f,
	    1.0f,
	});
	sprite.SetPosition({640.0f, 320.f});
	halfSize = {200.0f, 200.0f};

	status_ = std::make_unique<Status>();
	status_->Initialize({640.0f, 320.f}, halfSize, 150);

	halfSize /= 2.0f;
}

void Boss::PredictNextAction() {
	int ra = dist(g);
	if (index == 0) {
		if (stack) {
			enemyAction = ActionFactory::CreateAction("Debuff");
			enemyAction->Initialize(status_.get(), 0);
			enemyAction->SetStatusEffectName("AbsoluteReversal");
			enemyAction->SetStack(stack);
			enemyAction->SetBattleManager(battleManager_);
		}
		stack++;
	} else {
		bool is = false;
		if (ra <= 10) {
			enemyAction = ActionFactory::CreateAction("DebuffShield");
			enemyAction->Initialize(status_.get(), 10, 0, this);
			enemyAction->SetStatusEffectName("Weakening");
			enemyAction->SetStack(1);
			enemyAction->SetBattleManager(battleManager_);
			is = true;
		}
		ra -= 10;
		if (ra <= 20) {
			std::uniform_int_distribution<int> a(10, 20);
			enemyAction = ActionFactory::CreateAction("Atack");
			enemyAction->Initialize(status_.get(), a(g));
			enemyAction->SetBattleManager(battleManager_);
			is = true;
		}
		if (!is) {
			std::uniform_int_distribution<int> a(8, 12);
			enemyAction = ActionFactory::CreateAction("Atack");
			enemyAction->Initialize(status_.get(), a(g));
			enemyAction->SetBattleManager(battleManager_);
		}
	}
	index++;
	if (index >= 4) {
		index = 0;
	}
}

void Boss::StartBattlePeculiar() {}