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

void Asteroids::setConfig() {
	asteroidsSystem_->setAsteroidsConfig(10, 10, 10, 3);
	bulletsSystem_->setBulletsConfig(10, 10, 2);
	renderSystem_->setFighterClip({ 47, 90, 207, 250 });
	fighterSystem_->setFighterConfig(
		5.0, 2.0, 5.0, 0.995, 3,
		SDLK_UP, SDLK_LEFT, SDLK_RIGHT
	);
	fighterGunSystem_->setFighterGunConfig(250, SDLK_SPACE);
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


