#pragma once
#include <vector>
#include <KamataEngine.h>
using namespace KamataEngine;

class NumberSprite {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize(Vector2 pos, float size = 1.0f, const Vector2 anchor = {0.5f, 0.5f});

	/// <summary>
	/// 描画
	/// </summary>
	void Draw();

	void SetPosition(Vector2 pos);
	Vector2 GetPosition() const { return pos_; }

	void SetNumber(int num);

	void SetRotate(float rotate) {
		rotate_ = rotate;
		for (Sprite s : sprite) {
			s.SetRotation(rotate_);
		}
		SpritePos();
	}
	float GetRotate() const { return rotate_; }

private:

	int Number(int num, int num2 = 1);

	Sprite CreateSprite(int num);

	void SpritePos();

private:
	std::vector<Sprite> sprite;
	uint32_t TH;

	Vector2 pos_;
	float size_;
	const Vector2 cSize = {40.0f, 64.0f};

	float rotate_;

	Vector2 anchor_;

	bool is;
};
