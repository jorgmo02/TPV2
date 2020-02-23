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

	void updateScale();

public:
	Asteroid();
	Asteroid(Vector2D pos, Vector2D vel, double rot, int gen);
	void set(Vector2D pos, Vector2D vel, double rot, int gen);
	~Asteroid();

	void updatePos();

	inline bool inUse() {
		return inUse_;
	}

	inline void setInUse(bool inUse) {
		inUse_ = inUse;
	}

	inline int getGen() const {
		return gen_;
	}
	
	inline Vector2D getPos() const{
		return pos_;
	}

	inline int getWidth() const{
		return w_;
	}

	inline int getHeight() const{
		return h_;
	}

	inline int getRot() const{
		return rot_;
	}
};