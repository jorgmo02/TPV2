#pragma once
#include "Component.h"

struct Life : public Component
{
	Life(int lifes) : 
		Component(ecs::Lifes), //
		lifes_(lifes) //
	{}

	int lifes_ = 0;
};

