#pragma once

#include <SDL_stdinc.h> // for Uint32
#include "Component.h"

struct AsteroidGeneration : Component {
	AsteroidGeneration() : //
		generation_(3)
	{
	}

	Uint32 generation_;
};
