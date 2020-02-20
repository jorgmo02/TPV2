#pragma once
#include "Vector2D.h"

class Asteroid {
private:

	Vector2D pos_;
	Vector2D vel_;
	int w_;
	int h_;
	double rot_;
	int gen_;
	bool inUse_;
	int baseTam_;
	double baseRate_;

public:
	Asteroid();
	Asteroid(Vector2D pos, Vector2D vel, double rot, int gen);
	~Asteroid();

	bool inUse() {
		return inUse_;
	}

	void setInUse(bool inUse) {
		inUse_ = inUse;
	}
};

