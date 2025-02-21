#include "Blackout.h"

Blackout::~Blackout() { delete sp; }

void Blackout::Initialize() { 
	tx = TextureManager ::Load("white1x1.png");
	sp = new Sprite();
	sp->Initialize();
	sp->SetSize({1280.0f, 720.0f});
	isEnd = true;
}

void Blackout::Update() {
	if (!isWhite) {
		if (isMiddle) {

			middleTiner++;
			isStart = false;
			isEnd = false;
			float t = 1.0f - middleTiner / static_cast<float>(kBMiddleTimer);
			sp->SetColor({0.0f, 0.0f, 0.0f, t});
			if (middleTiner >= kBMiddleTimer) {

				isMiddle = false;
				isEnd = true;
				startTimer = 0;
				middleTiner = 0;
			}
		}
		if (isStart && !isMiddle) {
			if (startTimer >= kBStartTimer) {
				isMiddle = true;
			}
			startTimer++;
			float t = startTimer / static_cast<float>(kBStartTimer);
			sp->SetColor({0.0f, 0.0f, 0.0f, t});
		}
	} else {
		if (isMiddle) {

			middleTiner++;
			isStart = false;
			isEnd = false;
			float t = 1.0f - middleTiner / static_cast<float>(kWMiddleTimer);
			sp->SetColor({1.0f, 1.0f, 1.0f, t});
			if (middleTiner >= kWMiddleTimer) {
				isStart = false;
				isMiddle = false;
				isEnd = true;
				startTimer = 0;
				middleTiner = 0;
				isWhite = false;
			}
		}
		if (isStart && !isMiddle) {
			if (startTimer >= kWStartTimer) {
				isMiddle = true;
			}
			startTimer++;
			float t = startTimer / static_cast<float>(kWStartTimer);
			sp->SetColor({1.0f, 1.0f, 1.0f, t});
		}
	}
	
}

void Blackout::Draw() {
	// コマンドリストの取得
	ID3D12GraphicsCommandList* commandList = DirectXCommon::GetInstance()->GetCommandList();
#pragma region 前景スプライト描画
	// 前景スプライト描画前処理
	Sprite::PreDraw(commandList);

	/// <summary>
	/// ここに前景スプライトの描画処理を追加できる
	/// </summary>

	if (isStart || isMiddle) {
		sp->Draw();
	}
	// スプライト描画後処理
	Sprite::PostDraw();

}
