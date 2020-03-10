#pragma once

#include <vector>
#include "Manager.h"
#include "SDLGame.h"
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
	void readJson();
	void initEntities();
	void closeGame();
	void handleInput();
	void update();
	void render();

	SDLGame* game_;
	jute::jValue cfg_;	
	EntityManager* entityManager_;
	bool exit_;

	const static int _WINDOW_WIDTH_ = 640;
	const static int _WINDOW_HEIGHT_ = 480;

	const string DATA_FILE = "./resources/cfg/asteroids.cfg";

	int FONT_COLOR = 0x111122ff;

	int ASTEROID_SPEED = 10;
	int ASTEROIDS_PER_ROUND = 10;

	float BULLETS_SPEED = 2.0;
	float TIME_BETWEEN_SHOTS = 1;

	int NUM_LIFES = 3;

	float FIGHTER_IMPULSE = 5.0;
	float FIGHTER_SPEED_LIMIT = 2.0;
	float FIGHTER_RED_SPEED_RATE = 0.995;
};
