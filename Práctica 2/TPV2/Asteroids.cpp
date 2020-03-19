#include "SDL_macros.h"
#include "Asteroids.h"
#include <assert.h>

#include "ImageComponent.h"
#include "InputHandler.h"
#include "Transform.h"
#include "SDLGame.h"

#include "SDL_macros.h"

using namespace std;

Asteroids::Asteroids() :
		game_(nullptr), //
		mngr_(nullptr), //
		exit_(false) {
	initGame();
	loadFromJson();
	setConfig();
}

Asteroids::~Asteroids() {
	closeGame();
}

void Asteroids::initGame() {

	game_ = SDLGame::init("Asteroids", _WINDOW_WIDTH_, _WINDOW_HEIGHT_);

	AsteroidsPool::init(30);
	BulletsPool::init(10);

	mngr_ = new Manager(game_);

	renderSystem_ = mngr_->addSystem<RenderSystem>();
	collisionSystem_ = mngr_->addSystem<CollisionSystem>();
	gameCtrlSystem_ = mngr_->addSystem<GameCtrlSystem>();
	asteroidsSystem_ = mngr_->addSystem<AsteroidsSystem>();
	bulletsSystem_ = mngr_->addSystem<BulletsSystem>();  
	fighterSystem_ = mngr_->addSystem<FighterSystem>();
	fighterGunSystem_ = mngr_->addSystem<FighterGunSystem>();
}

void Asteroids::loadFromJson() {
	cfg_ = jute::parser::parse_file(CONFIG_FILE);

	ASTEROIDS_PER_ROUND = cfg_["asteroids"]["per round"].as_int();
	ASTEROIDS_VEL = cfg_["asteroids"]["speed"].as_int();
	ASTEROIDS_HEIGHT = cfg_["asteroids"]["height"].as_int();
	ASTEROIDS_WIDTH = cfg_["asteroids"]["width"].as_int();
	ASTEROIDS_GENS = cfg_["asteroids"]["gens"].as_int();

	BULLETS_WIDTH = cfg_["bullets"]["width"].as_int();
	BULLETS_HEIGHT = cfg_["bullets"]["height"].as_int();
	BULLETS_VEL = cfg_["bullets"]["speed"].as_int();

	FIGHTER_CLIP = {
		cfg_["fighter"]["clip"]["iniX"].as_int(),
		cfg_["fighter"]["clip"]["iniY"].as_int(),
		cfg_["fighter"]["clip"]["finX"].as_int(),
		cfg_["fighter"]["clip"]["finY"].as_int()
	};
	FIGHTER_MAX_LIFES = cfg_["lifes"].as_int();
	FIGHTER_IMPULSE = cfg_["fighter"]["impulse"].as_double();
	FIGHTER_SPEED_LIMIT = cfg_["fighter"]["speed limit"].as_double();
	FIGHTER_REDUCE_RATE = cfg_["fighter"]["red speed rate"].as_double();
	FIGHTER_TIME_BETWEEN_SHOOTS = cfg_["bullets"]["time"].as_double() * 1000;	// miliseconds
}

void Asteroids::setConfig() {
	asteroidsSystem_->setAsteroidsConfig(ASTEROIDS_WIDTH, ASTEROIDS_HEIGHT, ASTEROIDS_VEL, ASTEROIDS_GENS);
	bulletsSystem_->setBulletsConfig(BULLETS_WIDTH, BULLETS_HEIGHT, BULLETS_VEL);
	renderSystem_->setFighterClip(FIGHTER_CLIP);
	fighterSystem_->setFighterConfig(
		FIGHTER_IMPULSE, FIGHTER_SPEED_LIMIT, FIGHTER_ROTATION_RATE, FIGHTER_REDUCE_RATE, FIGHTER_MAX_LIFES,
		SDLK_UP, SDLK_LEFT, SDLK_RIGHT
	);
	fighterGunSystem_->setFighterGunConfig(FIGHTER_TIME_BETWEEN_SHOOTS, SDLK_SPACE);
	gameCtrlSystem_->setGameCtrlConfig(ASTEROIDS_PER_ROUND);
}

void Asteroids::closeGame() {
	delete mngr_;
}

void Asteroids::start() {
	exit_ = false;
	auto ih = InputHandler::instance();

	while (!exit_) {
		Uint32 startTime = game_->getTime();
		SDL_SetRenderDrawColor(game_->getRenderer(), COLOR(0x00AAAAFF));
		SDL_RenderClear(game_->getRenderer());

		ih->update();
		if (ih->keyDownEvent()) {
			if (ih->isKeyDown(SDLK_ESCAPE)) {
				exit_ = true;
				break;
			}
		}

		mngr_->refresh();

		gameCtrlSystem_->update();
		renderSystem_->update();
		if (gameCtrlSystem_->getGameState()->currentState_ == GameState::State::Started) {
			asteroidsSystem_->update();
			bulletsSystem_->update();
			fighterSystem_->update();
			fighterGunSystem_->update();
			collisionSystem_->update();
		}

		SDL_RenderPresent(game_->getRenderer());

		Uint32 frameTime = game_->getTime() - startTime;
		if (frameTime < 10)
			SDL_Delay(10 - frameTime);
	}
}


