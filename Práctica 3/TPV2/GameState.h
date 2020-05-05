#pragma once
#include "Component.h"
struct GameState : Component
{
	enum class State
	{
		Stopped,
		Started,
		Lose,
		Win
	};

	GameState() :
		currentState_(State::Stopped) {
	}

	State currentState_;
};

