#pragma once
#include "Vector2D.h"

class Bullet {
private:

	Vector2D pos_, vel_;
	int w_, h_;
	double rot_;
	bool inUse_;

public:
	Bullet();
	Bullet(Vector2D pos, Vector2D vel, double rot);
	void set(Vector2D pos, Vector2D vel, double rot);
	virtual ~Bullet();

	// GETTERS 

	inline bool inUse() const {
		return inUse_;
	}
	inline Vector2D getPos() const {
		return pos_;
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
	inline Vector2D getVel() const {
		return vel_;
	}

	// SETTERS

	inline void setPos(Vector2D pos) {
		pos_ = pos;
	}

	inline void setRot(double rot) {
		rot_ = rot;
	}

	inline void setInUse(bool inUse) {
		inUse_ = inUse;
	}
};