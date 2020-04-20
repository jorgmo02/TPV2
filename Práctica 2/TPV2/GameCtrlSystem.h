#pragma once

#include "ecs.h"
#include "System.h"
#include "Score.h"
#include "AsteroidsSystem.h"
#include "BulletsSystem.h"
#include "Score.h"
#include "GameState.h"
#include "FighterSystem.h"
#include "Health.h"

class GameCtrlSystem: public System {

public:

	virtual void recieve(const msg::Message& msg) override {
		switch (msg.id) {
		case msg::_FIGHTER_ASTEROID_COLLISION_:
			onFighterDeath(static_cast<const msg::FighterAsteroidCollisionMsg&>(msg).fighter_->getComponent<Health>()->health_);
			break;
		case msg::_NO_MORE_ASTEROIDS_:
			onAsteroidsExtinction();
			break;
		default:
			break;
		}
	}

	void onFighterDeath(int fighterHealth) {

		if(fighterHealth <= 0 )
			gameState_->currentState_ = GameState::State::Lose;
		else 
			gameState_->currentState_ = GameState::State::Stopped;
		mngr_->send<msg::Message>(msg::_DISABLE_ALL_);
	};

	void onAsteroidsExtinction() {
		gameState_->currentState_ = GameState::State::Win;
		mngr_->send<msg::Message>(msg::_DISABLE_ALL_);
	};

	void setConfig(int maxPlayerHealth) {
		maxLifes_ = maxPlayerHealth;
	}

	GameState* getGameState() const {
		return gameState_;
	};

	void init() override {
		Entity *e = mngr_->addEntity();
		auto sc = e->addComponent<Score>();
		gameState_ = e->addComponent<GameState>();
		sc->points_ = 0;
		mngr_->setHandler<_hdlr_GameState>(e);
	}

	void update() override {
		
		// juego parado
		if (gameState_->currentState_ == GameState::State::Stopped) {
			auto ih = game_->getInputHandler();

			if (ih->keyDownEvent() && ih->isKeyDown(SDLK_RETURN)) {
				mngr_->send<msg::Message>(msg::_NEW_TRY_);
				mngr_->getHandler<_hdlr_GameState>()->getComponent<Score>()->points_ = 0;
				gameState_->currentState_ = GameState::State::Started;
			}
		}

		// juego terminado -> reiniciar
		else if (gameState_->currentState_ != GameState::State::Started) {
			auto ih = game_->getInputHandler();
			if (ih->keyDownEvent() && ih->isKeyDown(SDLK_RETURN)) {
				gameState_->currentState_ = GameState::State::Stopped;
				mngr_->getHandler<_hdlr_GameState>()->getComponent<Score>()->points_ = 0;
				mngr_->getHandler<_hdlr_Fighter>()->getComponent<Health>()->health_ = maxLifes_;
			}
		}
	}

private:
	GameState* gameState_ = nullptr;
	int maxLifes_ = 3;
};

