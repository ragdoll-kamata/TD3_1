#pragma once
#include <memory>
#include <string>
class EnemyAction;
class ActionFactory {
public:
	/// <summary>
	/// アクションの生成
	/// </summary>
	/// <param name="statusEffectName">生成するアクションの名前</param>
	/// <returns>生成したアクション</returns>
	static std::unique_ptr<EnemyAction> CreateAction(std::string enemyname);

};
