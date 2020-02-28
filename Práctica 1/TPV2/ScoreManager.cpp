#include "ScoreManager.h"

ScoreManager::ScoreManager() :
	Component(ecs::ScoreManager), //
	running_(false), //
	end_(true),
	score_(0), //
	win_(false) //
{
}

ScoreManager::~ScoreManager() {
}
