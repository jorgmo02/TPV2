#include "FoodSystem.h"

#include "System.h"
#include "Entity.h"
#include "FoodPool.h"
#include "GameCtrlSystem.h"
#include "GameState.h"
#include "Manager.h"
#include "SDLGame.h"
#include "SDL_macros.h"

FoodSystem::FoodSystem() :
		System(ecs::_sys_Food), //
		numOfFoodPieces_(0) {
}

void FoodSystem::init() {
}

void FoodSystem::update() {
}

void FoodSystem::onEat(Entity *e) {
	// update score
	auto gameState = mngr_->getHandler(ecs::_hdlr_GameStateEntity)->getComponent<GameState>(ecs::GameState);
	gameState->score_++;

	game_->getAudioMngr()->playChannel(Resources::PacMan_Eat,0);

	// disbale food
	e->setActive(false);
	numOfFoodPieces_--;

	if ( numOfFoodPieces_ == 0)
		mngr_->getSystem<GameCtrlSystem>(ecs::_sys_GameCtrl)->onNoMoreFood();
}

void FoodSystem::addFood(std::size_t n) {


	RandomNumberGenerator *r = game_->getRandGen();

	// ghost width and height
	int width = 30;
	int height = 30;

	for (auto i(0u); i < n; i++) {

		int x = r->nextInt(10, game_->getWindowWidth() - width - 10);
		int y = r->nextInt(10, game_->getWindowHeight() - height - 10);
		Vector2D p(x, y);
		// add the entity
		Entity *e = mngr_->addEntity<FoodPool>(p, 30, 30);
		if (e != nullptr) {
			e->addToGroup(ecs::_grp_Food);
			numOfFoodPieces_++;
		}
	}
}

void FoodSystem::disableAll() {
	for (auto &e : mngr_->getGroupEntities(ecs::_grp_Food)) {
		e->setActive(false);
	}
	numOfFoodPieces_ = 0;
}
