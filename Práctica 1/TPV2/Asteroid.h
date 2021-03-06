#pragma once
#include "Vector2D.h"

class Asteroid {
private:

	Vector2D pos_, vel_;
	int w_, h_;
	double rot_;
	int gen_;
	bool inUse_;

	int baseTam_;
	double baseRate_;

	void updateScale();

public:
	Asteroid();
	Asteroid(Vector2D pos, Vector2D vel, double rot, int gen);
	virtual ~Asteroid();

	// GETTERS 

	inline bool inUse() const {
		return inUse_;
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
	inline Vector2D getVel() const{
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

	void set(Vector2D pos, Vector2D vel, double rot, int gen);
};