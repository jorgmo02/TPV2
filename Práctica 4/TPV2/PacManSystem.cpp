#include "PacManSystem.h"

#include "InputHandler.h"
#include "Manager.h"
#include "SDLGame.h"
#include "AnimatedImageComponent.h"
#include "GameState.h"


PacManSystem::PacManSystem() :
		System(ecs::_sys_PacMan), ///
		pacman_(nullptr), //
		tr_(nullptr) {
}

void PacManSystem::init() {
	pacman_ = mngr_->addEntity();

	tr_ = pacman_->addComponent<Transform>();
	resetPacManPosition();

	auto animatedImage = pacman_->addComponent<AnimatedImageComponent>();
	animatedImage->setFrameTime(100);
	Texture *spritesTex = game_->getTextureMngr()->getTexture(
			Resources::PacManSprites);
	for (int i = 0; i < 4; i++) {
		animatedImage->addFrame(spritesTex, { i * 128, 0, 128, 128 });
	}

	mngr_->setHandler(ecs::_hdlr_PacManEntity, pacman_);
}

void PacManSystem::recieve(const msg::Message& msg)
{
	switch (msg.id) {
	case msg::_GAME_RESET:
		resetPacManPosition();
		break;
	case msg::_PACMAN_DEAD:
		resetPacManPosition();
		loseLife();
		break;
	default:
		break;
	}
}

void PacManSystem::update() {

	auto gameState = mngr_->getHandler(ecs::_hdlr_GameStateEntity)->getComponent<GameState>(ecs::GameState);
	if ( gameState->state_ != GameState::RUNNING)
		return;

	auto ih = InputHandler::instance();
	assert(tr_ != nullptr);
	if (ih->keyDownEvent()) {
		if (ih->isKeyDown(SDLK_RIGHT)) {
			tr_->rotation_ = tr_->rotation_ + rotateRate_;
			tr_->velocity_ = tr_->velocity_.rotate(rotateRate_);
		}
		else if (ih->isKeyDown(SDLK_LEFT)) {
			tr_->rotation_ = tr_->rotation_ - rotateRate_;
			tr_->velocity_ = tr_->velocity_.rotate(-rotateRate_);
		}
		else if (ih->isKeyDown(SDLK_UP)) {
			Vector2D newVel = Vector2D(0, -1).rotate(tr_->rotation_);
			tr_->velocity_ = newVel * (tr_->velocity_.magnitude() + speedChangeRate_);
		}
		else if (ih->isKeyDown(SDLK_DOWN)) {
			Vector2D newVel = Vector2D(0, -1).rotate(tr_->rotation_);
			tr_->velocity_ = newVel * std::max(0.0, (tr_->velocity_.magnitude() - speedChangeRate_));
		}
	}

	// move, but stop on borders
	Vector2D oldPositions = tr_->position_;

	tr_->position_ = tr_->position_ + tr_->velocity_;
	int x = tr_->position_.getX();
	int y = tr_->position_.getY();

	if (x <= 0 || x + tr_->width_ >= game_->getWindowWidth() || y <= 0
			|| y + tr_->height_ >= game_->getWindowHeight()) {
		tr_->position_ = oldPositions;
		tr_->velocity_ = Vector2D(0.0, 0.0);
	}

}

void PacManSystem::resetPacManPosition() {
	tr_->width_ = tr_->height_ = 30.0;
	tr_->position_ = Vector2D( (game_->getWindowWidth()-tr_->width_)/2,
			(game_->getWindowHeight()-tr_->height_)/2);
	tr_->velocity_ = Vector2D(0.0, 0.0);
	tr_->rotation_ = 0.0;
}

void PacManSystem::loseLife() {
	if ((--lifes) <= 0) {
		mngr_->send<msg::Message>(msg::_GAME_OVER);
	}
}
