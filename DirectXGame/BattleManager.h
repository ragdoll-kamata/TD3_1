#pragma once
class BattleManager {
public:
	/// <summary>
	/// 初期化
	/// </summary>
	void Initialize();

	/// <summary>
	/// 毎フレーム処理
	/// </summary>
	void Update();




	static BattleManager* GetInstance();

private:
private:
	static BattleManager* instance;

	BattleManager() = default;
	~BattleManager() = default;
	BattleManager(BattleManager&) = default;
	BattleManager& operator=(BattleManager&) = default;
};
