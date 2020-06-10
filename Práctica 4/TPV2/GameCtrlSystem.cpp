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
		case msg::_PACMAN_DEAD:
			onPacManDeath();
			break;
		case msg::_NO_MORE_TSUKKIS:
			onNoMoreFood();
			break;
		default:
			break;
	}
}

void GameCtrlSystem::update() {

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
	//game_->getAudioMngr()->haltMusic();
	mngr_->send<msg::Message>(msg::_GAME_START);
	mngr_->send<msg::AddItemMessage>(msg::_ADD_TSUKKIS, 10);
	mngr_->send<msg::AddItemMessage>(msg::_ADD_GHOSTS, 2);
}

void GameCtrlSystem::resetGame() {
	gameState_->state_ = GameState::READY;
	gameState_->score_ = 0;
	gameState_->won_ = false;
	//game_->getAudioMngr()->playMusic(Resources::PacMan_Intro);
	mngr_->send<msg::Message>(msg::_GAME_RESET);
}
