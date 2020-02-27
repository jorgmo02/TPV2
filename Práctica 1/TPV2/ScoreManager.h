#pragma once

#include "Component.h"

class ScoreManager: public Component {
public:
	ScoreManager();
	ScoreManager(int pointsToWin);
	virtual ~ScoreManager();

	inline bool getScore() const {
		return score_;
	}

	void updateScore(int score);

	inline int getPointsToWin() const {
		return pointsToWin_;
	}

	inline void setPointsToWin(int pointsToWin) {
		pointsToWin_ = pointsToWin;
	}

	inline bool isRunning() const {
		return running_;
	}

	inline void setRunning(bool running) {
		running_ = running;
	}

	inline void setEnd(bool ended) {
		end_ = ended;
	}

	inline bool isGameOver() const {
		return end_;
	}

	inline bool hasWon() const {
		return score_ >= pointsToWin_;
	}

private:
	bool running_;
	bool end_;
	int score_;
	int pointsToWin_;
};
