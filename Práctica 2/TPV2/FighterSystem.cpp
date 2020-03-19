#include "FighterSystem.h"
#include "GameCtrlSystem.h"

void FighterSystem::onCollisionWithAsteroid(Entity* a) {
	health_->health_--;
	mngr_->getSystem<GameCtrlSystem>()->onFighterDeath(health_->health_);
	game_->getAudioMngr()->playChannel(Resources::Explosion, 0);
}