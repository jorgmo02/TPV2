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

	void onFighterDeath(int fighterHealth) {

		if(fighterHealth <= 0 )
			gameState_->currentState_ = GameState::State::Lose;
		else 
			gameState_->currentState_ = GameState::State::Stopped;
		disableAll();
	};

	void onAsteroidsExtinction() {
		gameState_->currentState_ = GameState::State::Win;
		disableAll();
	};

	void disableAll() {
		mngr_->getSystem<AsteroidsSystem>()->disableAsteroids();
		mngr_->getSystem<BulletsSystem>()->disableBullets();
		mngr_->getSystem<FighterSystem>()->reset();
		game_->getAudioMngr()->pauseMusic();
	}

	GameState* getGameState() const {
		return gameState_;
	};

	void setGameCtrlConfig(int asteroidsPerRound) {
		asteroidsPerRound_ = asteroidsPerRound;
	}

	void init() override {
		Entity *e = mngr_->addEntity();
		auto sc = e->addComponent<Score>();
		gameState_ = e->addComponent<GameState>();
		sc->points_ = 0;
		mngr_->setHandler<_hdlr_GameState>(e);

		game_->getAudioMngr()->pauseMusic();
	}

	void update() override {
		
		// juego parado
		if (gameState_->currentState_ == GameState::State::Stopped) {
			auto ih = game_->getInputHandler();

			if (ih->keyDownEvent() && ih->isKeyDown(SDLK_RETURN)) {
				mngr_->getSystem<AsteroidsSystem>()->addAsteroids(asteroidsPerRound_);
				mngr_->getHandler<_hdlr_GameState>()->getComponent<Score>()->points_ = 0;
				gameState_->currentState_ = GameState::State::Started;
				game_->getAudioMngr()->playMusic(Resources::MainTheme, -1);
				game_->getAudioMngr()->resumeMusic();
			}
		}

		// juego terminado -> reiniciar
		else if (gameState_->currentState_ != GameState::State::Started) {
			auto ih = game_->getInputHandler();
			if (ih->keyDownEvent() && ih->isKeyDown(SDLK_RETURN)) {
				gameState_->currentState_ = GameState::State::Stopped;
				mngr_->getHandler<_hdlr_GameState>()->getComponent<Score>()->points_ = 0;
				mngr_->getHandler<_hdlr_Fighter>()->getComponent<Health>()->health_ =
					mngr_->getSystem<FighterSystem>()->getMaxLifes();
			}
		}
	}

private:
	GameState* gameState_;
	int asteroidsPerRound_;
};

