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

	// falta por tocar Asteroid.cpp (tamaño y gens) y Bullet.cpp (tamaño)


	Entity* asteroidsPool = entityManager_->addEntity();
	AsteroidPool* aPool = asteroidsPool->addComponent<AsteroidPool>(10);	// variables hechas, 10 es la velocidad de asteroides
	asteroidsPool->addComponent<AsteroidsMotion>();							// variables hechas
	asteroidsPool->addComponent<AsteroidsViewer>();							// variables hechas

	Entity* bulletsPool = entityManager_->addEntity();						
	BulletsPool* bPool = bulletsPool->addComponent<BulletsPool>(2.0);		// variables hechas, 2.0 es la velocidad de las balas	
	bulletsPool->addComponent<BulletsMotion>();								// variables hechas
	bulletsPool->addComponent<BulletsViewer>();								// variables hechas

	Entity* caza = entityManager_->addEntity();								
	Transform* cazaTR = caza->addComponent<Transform>();					
	Health* cazaHealth = caza->addComponent<Health>(3);						// variables hechas, 3 es el número de vidas
	caza->addComponent<FighterViewer>();									// poner x, y, w, h para elegir el caza (posiblemente parametrizable)
	caza->addComponent<FighterCtrl>(SDLK_UP, SDLK_LEFT, SDLK_RIGHT,5.0, 2.0);// variables hechas, (SDL_Keycode forward, SDL_Keycode left, SDL_Keycode right, double thrust, double speedLimit)
	caza->addComponent<FighterMotion>(0.995);								// variables hechas, 0.995 es el reduceMovementRate
	caza->addComponent<Gun>(bPool);											// variables hechas, Gun::Gun(BulletsPool* p, SDL_Keycode shootKey, int timeBetweenShots)
	cazaTR->setPos(game_->getWindowWidth() / 2, game_->getWindowHeight() / 2);
	cazaTR->setWH(50, 50);													// leer de json?

	Entity *gameManager = entityManager_->addEntity();
	gameManager->addComponent<ScoreManager>();								// variables hechas
	gameManager->addComponent<GameLogic>(cazaTR, aPool, bPool, cazaHealth);	// variables hechas
	gameManager->addComponent<ScoreViewer>(0x111122ff);						// variables hechas, 0x111122ff es el color de las letras
	gameManager->addComponent<GameCtrl>(aPool, cazaHealth, 10);				// variables hechas, 10 es el número de asteroides por ronda
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