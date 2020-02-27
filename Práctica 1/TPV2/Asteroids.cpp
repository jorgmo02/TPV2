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

	Entity* asteroidsPool = entityManager_->addEntity();
	AsteroidPool* a = asteroidsPool->addComponent<AsteroidPool>();
	asteroidsPool->addComponent<AsteroidsMotion>();
	asteroidsPool->addComponent<AsteroidsViewer>();
	a->generateAsteroids(1);
	//a->onCollision(a->getPool()[0], nullptr);

	Entity* bulletsPool = entityManager_->addEntity();
	BulletsPool* b = bulletsPool->addComponent<BulletsPool>();
	bulletsPool->addComponent<BulletsMotion>();
	bulletsPool->addComponent<BulletsViewer>();

	Entity* caza = entityManager_->addEntity();
	Transform* cazaTR = caza->addComponent<Transform>();
	caza->addComponent<FighterViewer>();
	caza->addComponent<FighterCtrl>();
	caza->addComponent<FighterMotion>();
	caza->addComponent<Gun>(b);
	cazaTR->setPos(game_->getWindowWidth() / 2, game_->getWindowHeight() / 2);
	cazaTR->setWH(50, 50);
	caza->addComponent<Health>();

	Entity *gameManager = entityManager_->addEntity();
	gameManager->addComponent<ScoreManager>(1);
	gameManager->addComponent<GameLogic>(cazaTR);
	gameManager->addComponent<ScoreViewer>();
	gameManager->addComponent<GameCtrl>();
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

