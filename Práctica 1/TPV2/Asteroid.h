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

public:
	Asteroid();
	Asteroid(Vector2D pos, Vector2D vel, int w, int h, double rot, int gen);
	~Asteroid();

};

