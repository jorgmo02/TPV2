#include "GameCtrl.h"
#include "Entity.h"
#include "InputHandler.h"

GameCtrl::GameCtrl() :
	GameCtrl(nullptr, nullptr) {
}

GameCtrl::GameCtrl(AsteroidPool* a, Health* h) :
	Component(ecs::GameCtrl),
	health_(h),
	pool_(a),
	scoreManager_(nullptr),
	asteroidsGenerated(10) {
}

GameCtrl::~GameCtrl() {

}

void GameCtrl::init() {
	scoreManager_ = GETCMP1_(ScoreManager);
}

void GameCtrl::update() {

	if (InputHandler::instance()->keyDownEvent()) {
		if (!scoreManager_->isRunning()) {

			// inicia partida
			pool_->generateAsteroids(asteroidsGenerated);
			scoreManager_->setRunning(true);

			// rest the score if the game is over
			if (scoreManager_->isGameOver()) {
				scoreManager_->setLeftScore(0);
				scoreManager_->setRightScore(0);
			}
		}
	}
}

void GameCtrl::draw() {

	if (!scoreManager_->isRunning()) {
		Texture *hitanykey = game_->getTextureMngr()->getTexture(
				Resources::PressAnyKey);
		hitanykey->render(
				game_->getWindowWidth() / 2 - hitanykey->getWidth() / 2,
				game_->getWindowHeight() - hitanykey->getHeight() - 50);
	}

	// game over message when game is over
	if (scoreManager_->isGameOver()) {
		Texture *gameOver = game_->getTextureMngr()->getTexture(
				Resources::GameOver);
		gameOver->render(game_->getWindowWidth() / 2 - gameOver->getWidth() / 2,
				game_->getWindowHeight() - gameOver->getHeight() - 150);
	}
}