#pragma once
#include "Component.h"
#include "Transform.h"
#include "Entity.h"

class FighterMotion : public Component {

public:
	FighterMotion();
	FighterMotion(double reduceRate);
	~FighterMotion();

	void init() override;
	void update() override;

	bool insideBordersX() const;
	bool insideBordersY() const;

private:
	Transform* tr_;
	double reduceRate_;
};

