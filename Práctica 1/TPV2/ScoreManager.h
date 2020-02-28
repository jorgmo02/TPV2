#pragma once

#include "Component.h"
#include <iostream>

class ScoreManager: public Component {
public:
	ScoreManager();
	virtual ~ScoreManager();

	inline int getScore() const {
		return score_;
	}

	inline void sumPoint() {
		score_++;
	}
	
	inline void setPoints(int points) {
		score_ = points;
	}

	inline bool isRunning() const {
		return running_;
	}

	inline void setRunning(bool running) {
		running_ = running;
	}

	inline void setWin(bool win) {
		win_ = win;
	}

	inline void setGameOver(bool end) {
		end_ = end;
	}

	inline bool isGameOver() const {
		return end_;
	}

	inline bool isWin() const {
		return win_;
	}

private:
	bool running_;
	bool end_;
	bool win_;
	int score_;
};
