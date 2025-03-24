#pragma once
#include <KamataEngine.h>
using namespace KamataEngine;
class CardManager;
class Reward {
public:

	/// <summary>
	/// 初期化
	/// </summary>
	virtual void Initialize(CardManager* cardManager);

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	virtual void Update();

	/// <summary>
	/// 描画
	/// </summary>
	virtual void Draw();

	virtual void CardDraw();

	bool GetIs() const { return isR; }

	void SetIs(bool is) { isU = is; }

	bool IsDelete() { return isD; }

	void SetPos(Vector2 pos) { sp.SetPosition(pos); }

protected:
	Sprite sp;
	bool isR;
	bool isU;
	bool isD;
};
