#pragma once

#include <cmath>
#include "SDL_macros.h"
#include "SDLGame.h"
#include "System.h"
#include "Entity.h"
#include "AsteroidsPool.h"
#include "Manager.h"
#include "Score.h"
#include "AsteroidGeneration.h"
#include "Transform.h"

class AsteroidsSystem : public System {
public:

	void addAsteroids(int n)
	{
		for (int i = 0; i < n; i++)
			createRandomAsteroid();
	};

	virtual void recieve(const msg::Message& msg) override {
		switch (msg.id) {
		case msg::_BULLET_ASTEROID_COLLISION_:
			onCollisionWithBullet(static_cast<const msg::BulletAsteroidCollisionMsg&>(msg).asteroid_,
				static_cast<const msg::BulletAsteroidCollisionMsg&>(msg).bullet_);
			break;
		case msg::_DISABLE_ALL_:
			disableAsteroids();
			break;
		case msg::_NEW_TRY_:
			addAsteroids(asteroidsPerRound_);
			break;
		default:
			break;
		}
	}

	void disableAsteroids() {
		for (Entity* a : mngr_->getGroupEntities<_grp_Asteroids>())
			a->setActive(false);
		numOfAsteroids_ = 0;
	};

	void onCollisionWithBullet(Entity* a, Entity* b);

	void update() override {
		for (Entity* a : mngr_->getGroupEntities<_grp_Asteroids>())
		{
			if (a->isActive()) {
				Transform* tr = a->getComponent<Transform>();
				tr->position_ = tr->position_ + tr->velocity_;
				tr->rotation_ += asteroidsRotVel_;
				Vector2D oPos = tr->position_;

				if (oPos.getY() > game_->getWindowHeight())
					tr->position_ = Vector2D(tr->position_.getX(), 0);
				else if (oPos.getY() + tr->height_ < 0)
					tr->position_ = Vector2D(tr->position_.getX(), game_->getWindowHeight());

				if (oPos.getX() > game_->getWindowWidth())
					tr->position_ = Vector2D(0, tr->position_.getY());
				else if (oPos.getX() + tr->width_ < 0)
					tr->position_ = Vector2D(game_->getWindowWidth(), tr->position_.getY());
			}
		}
	};

	void setAsteroidsConfig(int w, int h, int vel, int rotVel, int asteroidsGens, int asteroidsPerRound) {
		asteroidsVel_ = vel;
		asteroidsWidth_ = w;
		asteroidsHeight_ = h;
		asteroidsRotVel_ = rotVel;
		asteroidsGens_ = asteroidsGens;
		asteroidsPerRound_ = asteroidsPerRound;
	}

private:

	std::size_t numOfAsteroids_ = 10;
	int asteroidsVel_ = 10;
	int asteroidsRotVel_ = 5;
	int asteroidsWidth_ = 10;
	int asteroidsHeight_ = 10;
	int asteroidsGens_ = 3;
	int asteroidsPerRound_ = 10;

	void createAsteroid(Transform* tr, int dir, int gen)
	{
		Entity* a = mngr_->addEntity<AsteroidsPool>(
			tr->position_,
			Vector2D(tr->velocity_.getY(), tr->velocity_.getX() * dir),
			tr->width_ / 1.5,
			tr->height_ / 1.5,
			gen
			);

		if (a != nullptr) {
			numOfAsteroids_++;
			a->addToGroup<_grp_Asteroids>();
		}
	};

	void createRandomAsteroid()
	{
		int h = game_->getWindowHeight();
		int w = game_->getWindowWidth();

		RandomNumberGenerator* random = game_->getRandGen();

		Vector2D r(random->nextInt(-50, 50), random->nextInt(-50, 50));	// margen con respecto al centro de la pantalla
		Vector2D pos(random->nextInt(0, w), random->nextInt(0, h));					// posición inicial del nuevo asteroide
		Vector2D target((Vector2D(w, h) / 2) + r);									// posición hacia la que se dirige el nuevo asteroide
		double m = random->nextInt(1, asteroidsVel_ + 1);								// número para multiplicar por el vector de velocidad
		int gen = random->nextInt(1, asteroidsGens_ + 1);											// generación inicial del asteroide
		Vector2D vel = (target - pos).normalize() * (m / 10.0);						// velocidad final del asteroide

		Entity* a = mngr_->addEntity<AsteroidsPool>(
			pos,
			vel,
			asteroidsWidth_ * gen,
			asteroidsHeight_ * gen,
			gen
			);

		if (a != nullptr) {
			numOfAsteroids_++;
			a->addToGroup<_grp_Asteroids>();
		}
	};
};

