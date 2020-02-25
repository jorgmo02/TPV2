#pragma once
#include "Vector2D.h"

class Bullet {
private:

	Vector2D pos_;
	Vector2D vel_;
	int w_;
	int h_;
	double rot_;
	bool inUse_;

public:
	Bullet();
	Bullet(Vector2D pos, Vector2D vel, double rot);
	void set(Vector2D pos, Vector2D vel, double rot);
	~Bullet();

	void updatePos();

	inline bool inUse() {
		return inUse_;
	}

	inline void setInUse(bool inUse) {
		inUse_ = inUse;
	}

	inline Vector2D getPos() const {
		return pos_;
	}

	inline Vector2D getVel() const {
		return vel_;
	}

	inline int getWidth() const {
		return w_;
	}

	inline int getHeight() const {
		return h_;
	}

	inline int getRot() const {
		return rot_;
	}
};