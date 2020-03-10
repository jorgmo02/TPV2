#include "BulletsViewer.h"

BulletsViewer::BulletsViewer() :
	Component(ecs::BulletsViewer),
	texture_(nullptr) {
}

BulletsViewer::~BulletsViewer() {
}

void BulletsViewer::init() {
	BulletsPool* bulletsPool_ = GETCMP1_(BulletsPool);
	pool_ = bulletsPool_->getPool();
	texture_ = game_->getTextureMngr()->getTexture(Resources::Bullet);
}

void BulletsViewer::draw() {
	SDL_Rect rect;
	for (auto o : pool_) {
		if (o->inUse()) {
			rect = RECT(o->getPos().getX(), o->getPos().getY(), o->getWidth(), o->getHeight());
			texture_->render(rect, o->getRot());
		}
	}
}
