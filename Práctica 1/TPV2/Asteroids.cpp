#include "SDL_macros.h"
#include "Asteroids.h"
#include <assert.h>

#include "AsteroidPool.h"
#include "AsteroidsMotion.h"
#include "AsteroidsViewer.h"
#include "BulletsMotion.h"
#include "BulletsPool.h"
#include "BulletsViewer.h"
#include "FighterCtrl.h"
#include "FighterMotion.h"
#include "FighterViewer.h"
#include "GameCtrl.h"
#include "GameLogic.h"
#include "Gun.h"
#include "Health.h"
#include "InputHandler.h"
#include "ScoreManager.h"
#include "ScoreViewer.h"
#include "SDLGame.h"
#include "Transform.h"

#include "SDL_macros.h"

using namespace std;

Asteroids::Asteroids() :
	game_(nullptr), //
	entityManager_(nullptr), //
	exit_(false) {
	initGame();
}

Asteroids::~Asteroids() {
	closeGame();
}

void Asteroids::initGame() {
	game_ = SDLGame::init("Asteroids", _WINDOW_WIDTH_, _WINDOW_HEIGHT_);
	entityManager_ = new EntityManager(game_);
	readJson();		// read game values from "./resources/cfg/asteroids.cfg"
	initEntities();
}

void Asteroids::readJson() {
	cfg_ = jute::parser::parse_file(DATA_FILE);

	FONT_COLOR = cfg_["font"]["color"].as_int();

	ASTEROIDS_PER_ROUND = cfg_["asteroids"]["per round"].as_int();
	ASTEROID_SPEED = cfg_["asteroids"]["speed"].as_int();

	BULLETS_SPEED = cfg_["bullets"]["speed"].as_double();
	TIME_BETWEEN_SHOTS = cfg_["bullets"]["time"].as_double() * 1000;	// miliseconds

	NUM_LIFES = cfg_["lifes"].as_int();

	FIGHTER_IMPULSE = cfg_["fighter"]["impulse"].as_double();
	FIGHTER_SPEED_LIMIT = cfg_["fighter"]["speed limit"].as_double();
	FIGHTER_RED_SPEED_RATE = cfg_["fighter"]["red speed rate"].as_double();
}

void Asteroids::initEntities() {

	Entity* asteroidsPool = entityManager_->addEntity();
	AsteroidPool* aPool = asteroidsPool->addComponent<AsteroidPool>(ASTEROID_SPEED);
	asteroidsPool->addComponent<AsteroidsMotion>();
	asteroidsPool->addComponent<AsteroidsViewer>();

	Entity* bulletsPool = entityManager_->addEntity();
	BulletsPool* bPool = bulletsPool->addComponent<BulletsPool>(BULLETS_SPEED);
	bulletsPool->addComponent<BulletsMotion>();
	bulletsPool->addComponent<BulletsViewer>();

	Entity* caza = entityManager_->addEntity();
	Transform* cazaTR = caza->addComponent<Transform>();
	Health* cazaHealth = caza->addComponent<Health>(NUM_LIFES);
	caza->addComponent<FighterViewer>();
	caza->addComponent<FighterCtrl>(SDLK_UP, SDLK_LEFT, SDLK_RIGHT, FIGHTER_IMPULSE, FIGHTER_SPEED_LIMIT);
	caza->addComponent<FighterMotion>(FIGHTER_RED_SPEED_RATE);
	caza->addComponent<Gun>(bPool, SDLK_SPACE, TIME_BETWEEN_SHOTS);
	cazaTR->setPos(game_->getWindowWidth() / 2, game_->getWindowHeight() / 2);
	cazaTR->setWH(50, 50);

	Entity* gameManager = entityManager_->addEntity();
	gameManager->addComponent<ScoreManager>();
	gameManager->addComponent<GameLogic>(cazaTR, aPool, bPool, cazaHealth);
	gameManager->addComponent<ScoreViewer>(FONT_COLOR);
	gameManager->addComponent<GameCtrl>(aPool, cazaHealth, ASTEROIDS_PER_ROUND);
}

void Asteroids::closeGame() {
	delete entityManager_;
}

void Asteroids::start() {
	exit_ = false;

	while (!exit_) {
		Uint32 startTime = game_->getTime();

		handleInput();
		update();
		render();

		Uint32 frameTime = game_->getTime() - startTime;
		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}
}

void Asteroids::stop() {
	exit_ = true;
}

void Asteroids::handleInput() {

	InputHandler *ih = InputHandler::instance();

	ih->update();

	if (ih->keyDownEvent()) {
		if (ih->isKeyDown(SDLK_ESCAPE)) {
			exit_ = true;
		}

		if (ih->isKeyDown(SDLK_f)) {
			int flags = SDL_GetWindowFlags(game_->getWindow());
			if (flags & SDL_WINDOW_FULLSCREEN) {
				SDL_SetWindowFullscreen(game_->getWindow(), 0);
			} else {
				SDL_SetWindowFullscreen(game_->getWindow(),
						SDL_WINDOW_FULLSCREEN);
			}
		}
	}

}

void Asteroids::update() {
	entityManager_->update();
}

void Asteroids::render() {
	SDL_SetRenderDrawColor(game_->getRenderer(), COLOR(0x00AAAAFF));
	SDL_RenderClear(game_->getRenderer());

	entityManager_->draw();

	SDL_RenderPresent(game_->getRenderer());
}