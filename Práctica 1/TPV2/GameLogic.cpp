#include "GameLogic.h"

GameLogic::GameLogic(Transform* cazaTR, AsteroidPool* aPool,
	BulletsPool* bPool, Health* health) :
	Component(ecs::GameLogic), //
	cazaTR_(cazaTR),
	aPool_(aPool),
	bPool_(bPool),
	health_(health),
	scoreManager_(nullptr) //
{
}

GameLogic::~GameLogic() {
}

void GameLogic::init() {
	// scoreManager_ = GETCMP2(ecs::ScoreManager,ScoreManager);
	scoreManager_ = GETCMP1_(ScoreManager);
}

void GameLogic::update() {
	if (!scoreManager_->isGameOver() && scoreManager_->isRunning()) {
		// check for collision of caza with items
		for (Asteroid* a : aPool_->getPool()) {
			if (a->inUse()) {
				checkWithFighter(a);
				checkWithBullets(a);
			}
		}
	}
}

void GameLogic::checkWithFighter(Asteroid* a) {
	if (Collisions::collidesWithRotation(
		cazaTR_->getPos(), cazaTR_->getW(), cazaTR_->getH(), cazaTR_->getRot(),
		a->getPos(), a->getWidth(), a->getHeight(), a->getRot()
	)) {
		health_->substractLife();
		reset();
		game_->getAudioMngr()->playChannel(Resources::ExplosionSound, 0);
		if (health_->getLifes() <= 0) {
			scoreManager_->setGameOver(true);
			scoreManager_->setWin(false);
		}
	}
}

void GameLogic::checkWithBullets(Asteroid* a) {
	for (Bullet* b : bPool_->getPool()) {
		if (b->inUse()) {
			if (Collisions::collidesWithRotation(
				a->getPos(), a->getWidth(), a->getHeight(), a->getRot(),
				b->getPos(), b->getWidth(), b->getHeight(), b->getRot()
			)) {
				aPool_->onCollision(a, b);
				bPool_->onCollision(a, b);
				scoreManager_->sumPoint();
				game_->getAudioMngr()->playChannel(Resources::GunShot, 0);

				if (aPool_->getNumOfAsteroid() <= 0) {
					scoreManager_->setGameOver(true);
					scoreManager_->setWin(true);
					reset();
				}
			}
		}
	}
}

void GameLogic::reset() {
	game_->getAudioMngr()->pauseMusic();
	scoreManager_->setRunning(false);
	aPool_->disableAll();
	bPool_->disableAll();

	cazaTR_->setVel(0, 0);
	cazaTR_->setPos(
		game_->getWindowWidth() / 2,
		game_->getWindowHeight() / 2
	);
	cazaTR_->setRot(0);
}

