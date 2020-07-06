#include "GameCtrlSystem.h"

#include "FoodSystem.h"
#include "SDLGame.h"
#include "Manager.h"
#include "GameState.h"
#include "GhostsSystem.h"
#include "PacManSystem.h"
#include "messages.h"


GameCtrlSystem::GameCtrlSystem() :
		System(ecs::_sys_GameCtrl), //
		gameState_(nullptr) {
}


void GameCtrlSystem::init() {
	Entity *e = mngr_->addEntity();
	gameState_ = e->addComponent<GameState>();
	mngr_->setHandler(ecs::_hdlr_GameStateEntity, e);
}

void GameCtrlSystem::recieve(const msg::Message& msg)
{
	switch (msg.id) {
		case msg::_GAME_OVER:
			onPacManDeath();
			break;
		case msg::_NO_MORE_TSUKKIS:
			onNoMoreFood();
			break;
		case msg::_GAME_START:
			mngr_->send<msg::AddItemMessage>(msg::_ADD_TSUKKIS, 10);
			mngr_->send<msg::AddItemMessage>(msg::_ADD_GHOSTS, 2);
			mngr_->send<msg::AddItemMessage>(msg::_ADD_BONUS, 1);
			break;
		case msg::_PACMAN_BONUS_COLLISION:
			bonusStartTime_ = game_->getTime();
			break;
		default:
			break;
	}
}

void GameCtrlSystem::update() {

	// timer del bonus
	if ((bonusStartTime_ + 10000 < game_->getTime() && gameState_->state_ == GameState::RUNNING)	// comprueba si ha pasado el tiempo dentro del juego
		|| gameState_->state_ == GameState::OVER) {	// también desactiva bonus si acaba la partida (imposible por diseño del juego, pero no molesta)
		mngr_->send<msg::Message>(msg::_BONUS_END);
	}

	if ( gameState_->state_ == GameState::RUNNING )
		return;

	auto ih = game_->getInputHandler();

	if ( ih->keyDownEvent() && ih->isKeyDown(SDLK_RETURN)) {
		switch ( gameState_->state_) {
			case GameState::READY:
				startGame();
				break;
			case GameState::OVER:
				resetGame();
				break;
			default:
				assert(false); // should not be rechable
				break;
		}
	}
}

void GameCtrlSystem::onPacManDeath() {
	gameState_->state_ = GameState::OVER;
	gameState_->won_ = false;
}

void GameCtrlSystem::onNoMoreFood() {
	gameState_->state_ = GameState::OVER;
	gameState_->won_ = true;
}

void GameCtrlSystem::startGame() {
	gameState_->state_ = GameState::RUNNING;
	mngr_->send<msg::Message>(msg::_GAME_START);
}

void GameCtrlSystem::resetGame() {
	gameState_->state_ = GameState::READY;
	gameState_->score_ = 0;
	gameState_->won_ = false;
	mngr_->send<msg::Message>(msg::_GAME_RESET);
}
