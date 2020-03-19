#pragma once

#include "Collisions.h"
#include "System.h"
#include "Manager.h"
#include "FighterSystem.h"
#include "BulletsSystem.h"
#include "AsteroidsSystem.h"
#include "Transform.h"

class CollisionSystem: public System {
public:
	void update() override {
		for (auto& a : mngr_->getGroupEntities<_grp_Asteroids>()) {
			if (a->isActive()) {
				Transform* tr = a->getComponent<Transform>();
				Transform* fighterTR = mngr_->getHandler<_hdlr_Fighter>()->getComponent<Transform>();

				// check with fighter
				if (Collisions::collidesWithRotation(
					fighterTR->position_, fighterTR->width_, fighterTR->height_, fighterTR->rotation_,
					tr->position_, tr->width_, tr->height_, tr->rotation_
				)) {
					mngr_->getSystem<FighterSystem>()->onCollisionWithAsteroid(a);
					break;
				}

				// check with bullets
				for (auto& b : mngr_->getGroupEntities<_grp_Bullets>()) {
					if (!b->isActive()) continue;
					if (!a->isActive()) break;
					Transform* bulletTR = b->getComponent<Transform>();
					if ((Collisions::collidesWithRotation(
						bulletTR->position_, bulletTR->width_, bulletTR->height_, bulletTR->rotation_,
						tr->position_, tr->width_, tr->height_, tr->rotation_
					))) {
						mngr_->getSystem<BulletsSystem>()->onCollisionWithAsteroid(a, b);
						mngr_->getSystem<AsteroidsSystem>()->onCollisionWithBullet(a, b);
					}
				}

			}
		}
	}
};

