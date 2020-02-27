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
	if (scoreManager_->isRunning()) {
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
		reset();
		health_->substractLife();
		if (health_->getLifes() <= 0) {
			scoreManager_->setRunning(false);
			scoreManager_->setEnd(true);
		}
		else
			aPool_->generateAsteroids(10);
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
				scoreManager_->updateScore(scoreManager_->getScore() + 1);
 				if (aPool_->getNumOfAsteroid() <= 0) {
					reset();
					scoreManager_->setRunning(false);
					scoreManager_->setEnd(true);
				}
			}
		}
	}
}

void GameLogic::reset() {
	aPool_->disableAll();
	bPool_->disableAll();
	cazaTR_->setVel(0, 0);
	cazaTR_->setPos(
		game_->getWindowWidth() / 2,
		game_->getWindowHeight() / 2
	);
}

