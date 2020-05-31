#include "GameCtrlSystem.h"

#include <cassert>
#include <cstdint>
#include "ecs.h"
#include "Entity.h"
#include "FighterInfo.h"
#include "FightersSystem.h"
#include "Manager.h"

using ecs::CmpId;

GameCtrlSystem::GameCtrlSystem() :
	System(ecs::_sys_GameCtrl) {
	state_ = READY;
	resetScore();
}

void GameCtrlSystem::init() {
	state_ = READY;
	mngr_->send<msg::PlayerInfoMsg>(mngr_->getClientName());
}

void GameCtrlSystem::update() {
	if (ready_) {
		if (state_ != RUNNING) {
			InputHandler* ih = game_->getInputHandler();
			if (ih->keyDownEvent() && ih->isKeyDown(SDLK_RETURN)) {
				mngr_->send<msg::Message>(msg::_PLAYERS_READY);
				startGame();
			}
		}
	}
}

void GameCtrlSystem::startGame() {
	if (state_ == GAMEOVER) {
		resetScore();
	}
	mngr_->getSystem<FightersSystem>(ecs::_sys_Fighters)->resetFighterPositions();
	state_ = RUNNING;
}

void GameCtrlSystem::onFighterDeath(uint8_t fighterId) {
	if (fighterId == 2) state_ = ROUNDOVER;
	else {
		assert(fighterId >= 0 && fighterId <= 1);

		if (state_ != ROUNDOVER)	// evitar el caso de que te puedan dar dos o más veces y quitarte más de una vida a la vez
		{
			uint8_t id = 1 - fighterId; // the id of the other player fighter

			state_ = ROUNDOVER;
			score[id]++;
			if (score[id] == 3) {
				thisPlayerWon_ = id == mngr_->getClientId();
				state_ = GAMEOVER;
			}
		}
	}
}

void GameCtrlSystem::recieve(const msg::Message& msg)
{
	switch (msg.id)
	{
	case msg::_PLAYER_INFO:
		if (msg.senderClientId != mngr_->getClientId()) mngr_->setOtherClientName(static_cast<const msg::PlayerInfoMsg&>(msg).name_);
		if (ready_ || msg.senderClientId == mngr_->getClientId()) return;
		ready_ = true;
		mngr_->send<msg::PlayerInfoMsg>(mngr_->getClientName());
		break;
	case msg::_PLAYERS_READY:
		if (state_ != RUNNING)
			startGame();
		break;
	case msg::_CLIENT_DISCONNECTED:
		ready_ = false;
		state_ = GAMEOVER;
		resetScore();
		mngr_->getSystem<FightersSystem>(ecs::_sys_Fighters)->resetFighterPositions();
		mngr_->setOtherClientName(" ");
		break;
	case msg::_FIGHTER_KILLED:
		if (msg.senderClientId == mngr_->getClientId()) return;
		onFighterDeath(static_cast<const msg::FighterKill&>(msg).playerId);
		break;
	default:
		break;
	}
}

void GameCtrlSystem::resetScore() {
	score[0] = score[1] = 0;
}