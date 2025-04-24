#include "StatusEffectPair.h"
#include <iostream>
#include <unordered_map>
#include <vector>
#include <memory>
#include <typeindex>
std::unordered_map<std::string, std::string> m = {
    {"Poison",       "Regeneration"},
    {"Regeneration", "Poison"      },
    {"AntiFragile",  "Fragility"   },
    {"Fragility",    "AntiFragile" },
    {"AurOfDeath",   "AurOfLife"   },
    {"AurOfLife",    "AurOfDeath"  },
};

std::string StatusEffectPair::GetStatusEffectType(std::string name) {
	if (m.contains(name)) {
		return m[name];
	}
	return "";
}
