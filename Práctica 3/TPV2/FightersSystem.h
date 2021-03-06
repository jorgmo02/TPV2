#pragma once

#include <SDL.h>
#include <cstdint>

#include "Entity.h"
#include "System.h"
#include "Vector2D.h"

class Transform;

class FightersSystem : public System {
public:
	FightersSystem();
	virtual ~FightersSystem();
	void init() override;
	virtual void recieve(const msg::Message& msg) override;
	void update() override;
	void resetFighterPositions();
private:
	void updateFighter(Entity* e);
	void motionFighter(Transform* tr);
	Entity* fighter0_;
	Entity* fighter1_;
};
