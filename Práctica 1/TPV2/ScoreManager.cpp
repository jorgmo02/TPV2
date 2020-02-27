#include "ScoreManager.h"

ScoreManager::ScoreManager() :
		ScoreManager(5) {
}

ScoreManager::ScoreManager(int pointsToWin) :
		Component(ecs::ScoreManager), //
		running_(false), //
		score_(0), //
		pointsToWin_(pointsToWin) //
{
}

ScoreManager::~ScoreManager() {
}

