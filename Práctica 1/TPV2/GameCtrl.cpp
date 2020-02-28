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
	game_->getAudioMngr()->playMusic(Resources::Imperial_March, -1);
	game_->getAudioMngr()->pauseMusic();
}

void GameCtrl::update() {

	if (InputHandler::instance()->keyDownEvent()) {
		if (!scoreManager_->isRunning()) {
			// inicia partida
			pool_->generateAsteroids(asteroidsGenerated);
			scoreManager_->setRunning(true);
			game_->getAudioMngr()->resumeMusic();

			// reset the score if the game is over
			if (scoreManager_->isGameOver()) {
				scoreManager_->setPoints(0);
				health_->setLifes(3);
				scoreManager_->setGameOver(false);
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
}