#include "Dummy.h"
using namespace MathUtility;
void Dummy::Initialize() {
	TH = TextureManager::GetInstance()->Load("white1x1.png");
	sprite.Initialize();
	sprite.SetTextureHandle(TH);
	sprite.SetAnchorPoint({0.5f, 0.5f});
	sprite.SetSize({60.0f, 60.0f});
	sprite.SetColor({1.0f,0.5f,0.0f,1.0f,});
	sprite.SetPosition({1000.0f,360.f});
	halfSize = {60.0f, 60.0f};
	halfSize /= 2.0f;


}
