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
#include "jute.h"

class Asteroids {

public:
	Asteroids();
	virtual ~Asteroids();

	// from SDLGame
	void start();
	void stop();

private:
	void initGame();
	void loadFromJson();
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

	jute::jValue cfg_;
	const string CONFIG_FILE = "./resources/cfg/asteroids.cfg";

	// asteroids config
	int ASTEROIDS_WIDTH = 10, ASTEROIDS_HEIGHT = 10, ASTEROIDS_GENS = 3, ASTEROIDS_VEL = 10, ASTEROIDS_ROT_VEL = 5, ASTEROIDS_PER_ROUND = 10;
	// bullets config
	int BULLETS_WIDTH = 10, BULLETS_HEIGHT = 10, BULLETS_VEL = 2;
	// fighter config
	double FIGHTER_IMPULSE = 5.0, FIGHTER_REDUCE_RATE = 0.995, FIGHTER_SPEED_LIMIT = 2.0, FIGHTER_ROTATION_RATE = 5.0;
	int FIGHTER_MAX_LIFES = 3, FIGHTER_TIME_BETWEEN_SHOOTS = 250;
	SDL_Rect FIGHTER_CLIP = { 47, 90, 207, 250 };
};
