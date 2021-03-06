#pragma once

#include "ecs.h"
#include "System.h"
#include "SDLGame.h"
#include "Manager.h"

class GameCtrlSystem : public System {
public:
	enum State : uint8_t {
		READY, RUNNING, ROUNDOVER, GAMEOVER
	};

	GameCtrlSystem();
	void init() override;
	void update() override;
	State getState() {
		return state_;
	}
	void onFighterDeath(uint8_t fighterId);
	uint8_t getScore(uint8_t fighterId) {
		assert(fighterId >= 0 && fighterId <= 1);
		return score[fighterId];
	}
	bool ready() const { return ready_; }
	void playersReady() { ready_ = true; }

	virtual void recieve(const msg::Message& msg) override;

	bool thisPlayerWon() const { return thisPlayerWon_; };

private:
	void resetScore();
	void startGame();

	bool ready_;

	bool thisPlayerWon_ = false;

	uint8_t score[2];
	State state_;
};
