#pragma once
#include "Singleton.h"
#include "ecs.h"
#include "Entity.h"
#include "ImageComponent.h"
#include "ObjectPool.h"
#include "Transform.h"
#include "AsteroidGeneration.h"

class AsteroidsPool : public Singleton<AsteroidsPool> {
	friend Singleton<AsteroidsPool>;

public:
	virtual ~AsteroidsPool() {
	};

	template <typename ...Targs>
	inline static Entity* construct(Targs&& ...args) {
		return AsteroidsPool::instance()->construct_(std::forward<Targs>(args)...);
	}

	inline static void destroy(Entity* p) {
		AsteroidsPool::instance()->destroy_(p);
	}

	inline Entity* construct_(Vector2D pos, Vector2D vel, double width, double height, int gen) {
		Entity* e = pool_.getObj();
		if (e != nullptr) {
			e->setActive(true);
			Transform* tr = e->getComponent<Transform>();
			tr->position_ = pos;
			tr->velocity_ = vel;
			tr->width_ = width;
			tr->height_ = height;
			e->getComponent<AsteroidGeneration>()->generation_ = gen;
		}
		return e;
	}

	inline void destroy_(Entity* p) {
		pool_.relObj(p);
	}

private:
	AsteroidsPool() :
		AsteroidsPool(10) {
	}

	AsteroidsPool(std::size_t n) :
		pool_(n) {
		for (Entity* e : pool_.getPool()) {
			e->addComponent<Transform>();
			e->addComponent<ImageComponent>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Asteroid));
			e->addComponent<AsteroidGeneration>();
		}
	}

	ObjectPool<Entity> pool_;
};

