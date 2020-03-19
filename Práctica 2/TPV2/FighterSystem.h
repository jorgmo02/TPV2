#pragma once

#include "SDLGame.h"
#include "System.h"
#include "Manager.h"
#include "GameCtrlSystem.h"
#include "Entity.h"
#include "InputHandler.h"
#include "Health.h"
#include "ImageComponent.h"
#include "Transform.h"

class FighterSystem : public System
{
public:
	FighterSystem() :
		fighter_(nullptr),
		tr_(nullptr) {
	}

	inline void setFighterConfig(
		double thrust, double speedLimit, double rotationRate, double reduceRate, int maxLifes,
		SDL_Keycode forward, SDL_Keycode left, SDL_Keycode right)
	{
		// values
		thrust_ = thrust;
		speedLimit_ = speedLimit;
		rotationRate_ = rotationRate;
		reduceRate_ = reduceRate;
		maxLifes_ = maxLifes;
		// keys
		forward_ = forward;
		left_ = left;
		right_ = right;
	}

	void init() override {
		fighter_ = mngr_->addEntity();
		tr_ = fighter_->addComponent<Transform>(
			Vector2D(game_->getWindowWidth() / 2, game_->getWindowHeight() / 2),	// pos
			Vector2D(),			// vel
			50, 50,				// width, height
			0					// rot
			);
		fighter_->addComponent<ImageComponent>(
			game_->getTextureMngr()->getTexture(Resources::Airplanes));
		health_ = fighter_->addComponent<Health>();
		mngr_->setHandler<_hdlr_Fighter>(fighter_);
	}

	void onCollisionWithAsteroid(Entity* a) {
		tr_->position_ = Vector2D(game_->getWindowWidth() / 2, game_->getWindowHeight() / 2);
		tr_->velocity_ = Vector2D(0, 0);
		mngr_->getSystem<GameCtrlSystem>()->onFighterDeath();
		/*health_->substractLife();
		scoreManager_->setRunning(false);
		reset();
		game_->getAudioMngr()->playChannel(Resources::ExplosionSound, 0);
		if (health_->getLifes() <= 0) {
			scoreManager_->setGameOver(false);
		}*/
	}

	void update() override {

		// fighter control
		auto ih = InputHandler::instance();
		assert(tr_ != nullptr);
		
		if (ih->keyDownEvent()) {
			if (ih->isKeyDown(forward_)) {
				Vector2D newVel = tr_->velocity_ + Vector2D(0, -1).rotate(tr_->rotation_) * thrust_;

				if (newVel.magnitude() > speedLimit_)
					newVel = newVel.normalize() * speedLimit_;

				tr_->velocity_ = newVel;
			}
			else if (ih->isKeyDown(left_)) {
				tr_->rotation_ -= rotationRate_;
			}
			else if (ih->isKeyDown(right_)) {
				tr_->rotation_ += rotationRate_;
			}
		}

		// fighter movement
		tr_->position_ = tr_->position_ + tr_->velocity_;
		tr_->velocity_ = tr_->velocity_ * reduceRate_;

		int x = tr_->position_.getX();
		int y = tr_->position_.getY();

		if (x <= 0 || x + tr_->width_ >= game_->getWindowWidth()) {
			tr_->velocity_ =
				Vector2D(tr_->velocity_.getX() * -1,
					tr_->velocity_.getY());
		}
		if (y <= 0 || y + tr_->height_ >= game_->getWindowHeight()) {
			tr_->velocity_ =
				Vector2D(tr_->velocity_.getX(),
					tr_->velocity_.getY() * -1);
		}
	}

private:
	Entity* fighter_;
	Transform* tr_;
	Health* health_;

	double thrust_;
	double speedLimit_;
	double rotationRate_;
	double reduceRate_;
	int maxLifes_;

	SDL_Keycode forward_, left_, right_;
};

