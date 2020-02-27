#include "ScoreManager.h"

ScoreManager::ScoreManager() :
		ScoreManager(5) {
}

ScoreManager::ScoreManager(int pointsToWin) :
	Component(ecs::ScoreManager), //
	running_(false), //
	end_(false),
	score_(0), //
	pointsToWin_(pointsToWin) //
{
}

ScoreManager::~ScoreManager() {
}

void ScoreManager::updateScore(int score)
{
	score_ = score;
	end_ = score_ >= pointsToWin_;
}

