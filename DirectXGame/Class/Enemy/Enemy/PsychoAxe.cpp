#include "PsychoAxe.h"
#include "ActionFactory.h"
using namespace MathUtility;
void PsychoAxe::Initialize() {
	TH = TextureManager::GetInstance()->Load("white1x1.png");
	sprite.Initialize();
	sprite.SetTextureHandle(TH);
	sprite.SetAnchorPoint({0.5f, 0.5f});
	sprite.SetSize({60.0f, 120.0f});
	sprite.SetColor({
	    1.0f,
	    0.5f,
	    0.0f,
	    1.0f,
	});
	sprite.SetPosition({640.0f, 320.f});
	halfSize = {60.0f, 120.0f};

	status_ = std::make_unique<Status>();
	status_->Initialize({640.0f, 320.f}, halfSize, 100);

	halfSize /= 2.0f;
}

void PsychoAxe::PredictNextAction() {
	if (index < 3) {
		enemyAction = ActionFactory::CreateAction("ContinuousAttack");
		enemyAction->Initialize(status_.get(), 3, 3);
		enemyAction->SetBattleManager(battleManager_);
		index++;
	} else if(index == 3) {
		enemyAction = ActionFactory::CreateAction("ContinuousHeal");
		enemyAction->Initialize(status_.get(), 5, 4, this);
		enemyAction->SetBattleManager(battleManager_);
		index++;
	} else {
		enemyAction = ActionFactory::CreateAction("Buff");
		enemyAction->Initialize(status_.get(), 2, 0, this);
		enemyAction->SetBattleManager(battleManager_);
		enemyAction->SetStatusEffectName("AuraOfDeath");
		enemyAction->SetStack(2);
		index = 0;
	}
}

void PsychoAxe::StartBattlePeculiar() {}
