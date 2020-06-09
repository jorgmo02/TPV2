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
	game_->getAudioMngr()->playMusic(Resources::PacMan_Intro);
}

void GameCtrlSystem::update() {

	if ( gameState_->state_ == GameState::RUNNING )
		return;

	auto ih = game_->getInputHandler();

	if ( ih->keyDownEvent() && ih->isKeyDown(SDLK_RETURN)) {
		switch ( gameState_->state_) {
		case GameState::READY:
			gameState_->state_ = GameState::RUNNING;
			game_->getAudioMngr()->haltMusic();
			startGame();
			break;
		case GameState::OVER:
			gameState_->state_ = GameState::READY;
			gameState_->score_ = 0;
			gameState_->won_ = false;
			game_->getAudioMngr()->playMusic(Resources::PacMan_Intro);
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
	mngr_->getSystem<GhostsSystem>(ecs::_sys_Ghosts)->disableAll();
	mngr_->getSystem<FoodSystem>(ecs::_sys_Food)->disableAll();
	game_->getAudioMngr()->haltMusic();
	game_->getAudioMngr()->playChannel(Resources::PacMan_Death,0);
}

void GameCtrlSystem::onNoMoreFood() {
	gameState_->state_ = GameState::OVER;
	gameState_->won_ = true;
	mngr_->getSystem<GhostsSystem>(ecs::_sys_Ghosts)->disableAll();
	mngr_->getSystem<FoodSystem>(ecs::_sys_Food)->disableAll();
	game_->getAudioMngr()->haltMusic();
	game_->getAudioMngr()->playChannel(Resources::PacMan_Won,0);
}

void GameCtrlSystem::startGame() {
	mngr_->send<msg::Message>(msg::_GAME_START);
	mngr_->getSystem<FoodSystem>(ecs::_sys_Food)->addFood(10);
	mngr_->getSystem<GhostsSystem>(ecs::_sys_Ghosts)->addGhosts(2);
	mngr_->getSystem<PacManSystem>(ecs::_sys_PacMan)->resetPacManPosition();
}
