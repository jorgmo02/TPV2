#include "ScoreManager.h"

ScoreManager::ScoreManager() :
	Component(ecs::ScoreManager), //
	score_(0), //
	gameState_(GameState::Stopped)
{
}

ScoreManager::~ScoreManager() {
}
