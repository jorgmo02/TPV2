#pragma once

#include "SDL_macros.h"
#include "System.h"
#include "Manager.h"
#include "Entity.h"
#include "BulletsPool.h"
#include "Transform.h"

class BulletsSystem : public System {
public:

	void onCollisionWithAsteroid(Entity* a, Entity* b) {
		b->setActive(false);
	};

	void disableBullets() {
		for (Entity* a : mngr_->getGroupEntities<_grp_Bullets>())
			a->setActive(false);
	}

	void shoot(Vector2D pos, Vector2D vel, double w, double h, double rot) {

		Vector2D bulletPos = pos + Vector2D(w / 2, h / 2) + Vector2D(0, -(h / 2)).rotate(rot);

		Entity* b = mngr_->addEntity<BulletsPool>(
			bulletPos,
			Vector2D(0, -1).rotate(rot) * bulletsVel_,
			bulletsWidth_,
			bulletsHeight_,
			rot
			);

		if (b != nullptr) {
			b->addToGroup<_grp_Bullets>();
		}
	};

	void update() override {
		for (Entity* b : mngr_->getGroupEntities<_grp_Bullets>())
		{
			if (b->isActive()) {
				Transform* tr = b->getComponent<Transform>();
				tr->position_ = tr->position_ + tr->velocity_;
				Vector2D oPos = tr->position_;

				if (oPos.getY() > game_->getWindowHeight() || oPos.getY() + tr->height_ < 0 ||
					oPos.getX() > game_->getWindowWidth() || oPos.getX() + tr->width_ < 0)
					b->setActive(false);
			}
		}
	};

	void setBulletsConfig(int w, int h, int vel) {
		bulletsVel_ = vel;
		bulletsWidth_ = w;
		bulletsHeight_ = h;
	};

private:
	int bulletsVel_;
	int bulletsWidth_;
	int bulletsHeight_;
};