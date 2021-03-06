#include "FoodSystem.h"

#include "System.h"
#include "Entity.h"
#include "FoodPool.h"
#include "GameCtrlSystem.h"
#include "GameState.h"
#include "Manager.h"
#include "SDLGame.h"
#include "SDL_macros.h"
#include "IsBonus.h"

FoodSystem::FoodSystem() :
		System(ecs::_sys_Food), //
		numOfFoodPieces_(0) {
}

void FoodSystem::init() {
}

void FoodSystem::recieve(const msg::Message& msg)
{
	switch (msg.id) {
		// los dos casos deshabilitan la comida
		case msg::_NO_MORE_TSUKKIS:
		case msg::_GAME_OVER:
			disableAll();
			break;
		// a�ade comida
		case msg::_ADD_TSUKKIS:
			addFood(static_cast<const msg::AddItemMessage&>(msg).numItems_);
			break;
		case msg::_ADD_BONUS:
			addFood(static_cast<const msg::AddItemMessage&>(msg).numItems_, true);
			break;
		// pacman come una cereza
		case msg::_PACMAN_TSUKKI_COLLISION:
			onEat(static_cast<const msg::CollisionMessage&>(msg).collidedWith_);
			break;
		case msg::_PACMAN_BONUS_COLLISION:
			onEat(static_cast<const msg::CollisionMessage&>(msg).collidedWith_);
			break;
		default:
			break;
	}
}

void FoodSystem::update() {
}

// pacman come una cereza
void FoodSystem::onEat(Entity *e) {

	// disable food
	e->setActive(false);

	// comprobar si es una fruta o un bonus sabiendo si tiene componente IsBonus
	if (e->getComponent<IsBonus>(ecs::IsBonus) == nullptr)
	{
		// update score
		auto gameState = mngr_->getHandler(ecs::_hdlr_GameStateEntity)->getComponent<GameState>(ecs::GameState);
		gameState->score_++;
		numOfFoodPieces_--;
		if (numOfFoodPieces_ == 0)
			mngr_->send<msg::Message>(msg::_NO_MORE_TSUKKIS);
	}
}

void FoodSystem::addFood(std::size_t n, bool makeBonus) {

	RandomNumberGenerator *r = game_->getRandGen();

	// food width and height
	int width = 30;
	int height = 30;

	for (unsigned int i(0u); i < n; i++) {

		int x = r->nextInt(10, game_->getWindowWidth() - width - 10);
		int y = r->nextInt(10, game_->getWindowHeight() - height - 10);
		Vector2D p(x, y);

		// add the entity
		Entity *e = mngr_->addEntity<FoodPool>(p, 30, 30);
		if (e != nullptr)
		{
			// add a bonus
			if (makeBonus) {
				e->addComponent<IsBonus>();
				// se explica por qu� uso dos grupos diferentes en update de CollisionSystem
				e->addToGroup(ecs::_grp_Bonus);
				AnimatedImageComponent* aImg = e->getComponent<AnimatedImageComponent>(ecs::AnimatedImageComponent);
				aImg->reset();
				Texture* spritesTex = SDLGame::instance()->getTextureMngr()->getTexture(Resources::PacManSprites);
				aImg->addFrame(spritesTex, { 128 * 6, 128, 128, 128 });
			}
			// add normal food
			else {
				e->addToGroup(ecs::_grp_Food);
				numOfFoodPieces_++;
			}
		}
	}
}

void FoodSystem::disableAll() {
	for (auto &e : mngr_->getGroupEntities(ecs::_grp_Food)) {
		e->setActive(false);
	}
	for (auto &e : mngr_->getGroupEntities(ecs::_grp_Bonus)) {
		e->setActive(false);
	}
	numOfFoodPieces_ = 0;
}
