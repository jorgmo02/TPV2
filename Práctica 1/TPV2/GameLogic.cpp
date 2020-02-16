#include "GameLogic.h"
#include "Collisions.h"
#include "Resources.h"
#include "Entity.h"

GameLogic::GameLogic(Transform* cazaTR) :
		Component(ecs::GameLogic), //
		cazaTR_(cazaTR),
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
	// check for collision of cazq with items
	/*if (Collisions::collides(cazaTR_->getPos(), cazaTR_->getW(),
			cazaTR_->getH(), otroObjetoTR_->getPos(), otroObjetoTR_->getW(),
			otroObjetoTR_->getH())) {
	}*/
}

