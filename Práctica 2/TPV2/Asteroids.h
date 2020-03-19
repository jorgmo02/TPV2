#pragma once

#include <vector>

#include "CollisionSystem.h"
#include "GameCtrlSystem.h"
#include "Manager.h"
#include "RenderSystem.h"
#include "SDLGame.h"
#include "BulletsSystem.h"
#include "FighterSystem.h"
#include "FighterGunSystem.h"

class Asteroids {

public:
	Asteroids();
	virtual ~Asteroids();

	// from SDLGame
	void start();
	void stop();

private:
	void initGame();
	void setConfig();
	void closeGame();

	SDLGame *game_;
	Manager *mngr_;
	bool exit_;

	RenderSystem *renderSystem_;
	CollisionSystem *collisionSystem_;
	GameCtrlSystem *gameCtrlSystem_;
	AsteroidsSystem* asteroidsSystem_;
	BulletsSystem* bulletsSystem_;
	FighterSystem* fighterSystem_;
	FighterGunSystem* fighterGunSystem_;

	const static int _WINDOW_WIDTH_ = 640;
	const static int _WINDOW_HEIGHT_ = 480;

	int ASTEROIDS_WIDTH;
	int ASTEROIDS_HEIGHT;
};
