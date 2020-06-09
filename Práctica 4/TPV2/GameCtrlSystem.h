#pragma once

#include "System.h"

struct GameState;

class GameCtrlSystem: public System {
public:

	GameCtrlSystem();

	void init() override;
	void update() override;

	// TODO: these methods should go private
	void onPacManDeath();
	void onNoMoreFood();

private:
	void startGame();

	GameState *gameState_;

};

