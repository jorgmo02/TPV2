#pragma once
#include "Component.h"
struct Health : Component
{
	Health(int health) :
		health_(health) {
	}

	Health() : Health(3) { };

	int health_;
};

