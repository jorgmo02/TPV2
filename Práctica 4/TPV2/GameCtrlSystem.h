#pragma once

#include "System.h"

struct GameState;

class GameCtrlSystem: public System {
public:

	GameCtrlSystem();

	void init() override;
	virtual void recieve(const msg::Message& msg) override;
	void update() override;

private:
	void onPacManDeath();
	void onNoMoreFood();
	void startGame();
	void resetGame();

	GameState *gameState_;

};

