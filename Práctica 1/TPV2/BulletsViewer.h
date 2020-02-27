#pragma once
#include "Component.h"
#include "BulletsPool.h"
#include "SDL_macros.h"
#include "Entity.h"

class BulletsViewer : public Component {
public:
	BulletsViewer();
	virtual ~BulletsViewer();
	void init() override;
	void draw() override;

private:
	vector<Bullet*> pool_;
	Texture* texture_;
};

