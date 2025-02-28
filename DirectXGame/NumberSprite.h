#pragma once
#include <vector>
#include <KamataEngine.h>
using namespace KamataEngine;

enum class Center {
	Left,
	Central,
	Right,
};

class NumberSprite {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Vector2 pos, const Center centor = Center::Central);

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();


	void SetNumber(int num);

private:

	Sprite CreateSprite(int num);

private:
	Center centor_;
	std::vector<Sprite> sprite;
	uint32_t TH;

	Vector2 pos_;
	Vector2 size;
};
