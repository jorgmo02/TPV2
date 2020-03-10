#pragma once

#include "Component.h"
#include <iostream>

class GameState {
public:
	enum States : int {
		Running,
		Stopped,
		Win,
		Lose
	};
};

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
		return gameState_ == GameState::Running;
	}

	inline void setRunning(bool running) {
		(running) ?
			gameState_ = GameState::Running :
			gameState_ = GameState::Stopped;
	}

	inline void setGameOver(bool win) {
		(win) ?
			gameState_ = GameState::Win :
			gameState_ = GameState::Lose;
	}

	inline bool isGameOver() const {
		return gameState_ == GameState::Win ||
			gameState_ == GameState::Lose;
	}

	inline bool isWin() const {
		return gameState_ == GameState::Win;
	}

private:
	int score_;
	GameState::States gameState_;
};
