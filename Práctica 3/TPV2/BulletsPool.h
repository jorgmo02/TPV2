#pragma once
#include "Singleton.h"
#include "ecs.h"
#include "Entity.h"
#include "ImageComponent.h"
#include "ObjectPool.h"
#include "Transform.h"

class BulletsPool : public Singleton<BulletsPool> {
	friend Singleton<BulletsPool>;

public:
	virtual ~BulletsPool() {
	};

	template <typename ...Targs>
	inline static Entity* construct(Targs&& ...args) {
		return BulletsPool::instance()->construct_(std::forward<Targs>(args)...);
	}

	inline static void destroy(Entity* p) {
		BulletsPool::instance()->destroy_(p);
	}

	inline Entity* construct_(Vector2D pos, Vector2D vel, double width, double height, double rot) {
		Entity* e = pool_.getObj();
		if (e != nullptr) {
			e->setActive(true);
			Transform* tr = e->getComponent<Transform>();
			tr->position_ = pos;
			tr->velocity_ = vel;
			tr->width_ = width;
			tr->height_ = height;
			tr->rotation_ = rot;
		}
		return e;
	}

	inline void destroy_(Entity* p) {
		pool_.relObj(p);
	}

private:
	BulletsPool() :
		BulletsPool(30) {
	}

	BulletsPool(std::size_t n) :
		pool_(n) {
		for (Entity* e : pool_.getPool()) {
			e->addComponent<Transform>();
			e->addComponent<ImageComponent>(SDLGame::instance()->getTextureMngr()->getTexture(Resources::Bullet));
		}
	}

	ObjectPool<Entity> pool_;
};

