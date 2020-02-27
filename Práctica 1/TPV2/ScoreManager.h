#pragma once

#include "Component.h"

class ScoreManager: public Component {
public:
	ScoreManager();
	ScoreManager(int pointsToWin);
	virtual ~ScoreManager();

	int getScore() const {
		return score_;
	}

	void setScore(int score) {
		score_ = score;
	}

	int getRounds() const {
		return pointsToWin_;
	}

	void setPointsToWin(int pointsToWin) {
		pointsToWin_ = pointsToWin;
	}

	bool isRunning() const {
		return running_;
	}

	void setRunning(bool running) {
		running_ = running;
	}

	bool isGameOver() {
		return score_ == pointsToWin_;
	}

private:
	bool running_;
	int score_;
	int pointsToWin_;
};
