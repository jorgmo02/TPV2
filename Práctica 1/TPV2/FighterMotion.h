#pragma once
#include "Component.h"
class FighterMotion : public Component {
public:
	FighterMotion();
	~FighterMotion();

	void accelerate();
	// = tr_->setVel(tr_->getVel() + Vector2D(0, -1) * thrust (= factor de empuje, double));

private:
	double thrust;
};

