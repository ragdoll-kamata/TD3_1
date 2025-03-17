#pragma once
#include <memory>
#include <string>
class StatusEffect;
class StatusEffectFactory {
public:
	/// <summary>
	/// ステータスエフェクトの生成
	/// </summary>
	/// <param name="statusEffectName">生成するステータスエフェクトの名前</param>
	/// <returns>生成したステータスエフェクト</returns>
	static std::unique_ptr<StatusEffect> CreateStatusEffect(std::string statusEffectName);

};
