#include "StatusEffectPair.h"
#include <iostream>
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <vector>
std::unordered_map<std::string, std::string> m = {
    {"Poison",       "Regeneration"},
    {"Regeneration", "Poison"      },
    {"AntiFragile",  "Fragility"   },
    {"Fragility",    "AntiFragile" },
    {"AurOfDeath",   "AurOfLife"   },
    {"AurOfLife",    "AurOfDeath"  },
    {"Weakening",    "Strongening" },
    {"Strongening",  "Weakening"   },
};

std::string StatusEffectPair::GetStatusEffectType(std::string name) {
	if (m.contains(name)) {
		return m[name];
	}
	return "";
}
