#pragma once

#include <cstring>

#include "Component.h"

struct FighterInfo : Component {
	FighterInfo(uint8_t fighterId, string fighterName = "") :
		Component(ecs::FighterInfo), fighterId(fighterId), name(fighterName) {
	}

	uint8_t fighterId;
	string name;
};
