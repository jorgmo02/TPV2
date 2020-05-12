#include "Collisions.h"

Collisions::Collisions() {
}

Collisions::~Collisions() {
}

bool Collisions::collidesWithRotation(const Vector2D o1Pos, double o1Width, double o1Height, double o1Rot, const Vector2D o2Pos, double o2Width, double o2Height, double o2Rot) {
	Vector2D Ac = o1Pos + Vector2D(o1Width / 2.0, o1Height / 2.0);

	double angleA = o1Rot;

	Vector2D Alu = Ac
		+ Vector2D(-o1Width / 2.0, -o1Height / 2.0).rotate(angleA);
	Vector2D Aru = Ac
		+ Vector2D(o1Width / 2.0, -o1Height / 2.0).rotate(angleA);
	Vector2D All = Ac
		+ Vector2D(-o1Width / 2.0, o1Height / 2.0).rotate(angleA);
	Vector2D Arl = Ac
		+ Vector2D(o1Width / 2.0, o1Height / 2.0).rotate(angleA);

	double angleB = o2Rot;

	Vector2D Bc = o2Pos + Vector2D(o2Width / 2.0, o2Height / 2.0);

	Vector2D Blu = Bc
		+ Vector2D(-o2Width / 2.0, -o2Height / 2.0).rotate(angleB);
	Vector2D Bru = Bc
		+ Vector2D(o2Width / 2.0, -o2Height / 2.0).rotate(angleB);
	Vector2D Bll = Bc
		+ Vector2D(-o2Width / 2.0, o2Height / 2.0).rotate(angleB);
	Vector2D Brl = Bc
		+ Vector2D(o2Width / 2.0, o2Height / 2.0).rotate(angleB);

	return PointInRectangle(Alu, Aru, All, Arl, Blu)
		|| PointInRectangle(Alu, Aru, All, Arl, Bru)
		|| PointInRectangle(Alu, Aru, All, Arl, Bll)
		|| PointInRectangle(Alu, Aru, All, Arl, Brl)
		|| PointInRectangle(Blu, Bru, Bll, Brl, Alu)
		|| PointInRectangle(Blu, Bru, Bll, Brl, Aru)
		|| PointInRectangle(Blu, Bru, Bll, Brl, All)
		|| PointInRectangle(Blu, Bru, Bll, Brl, Arl);
}

bool Collisions::PointInRectangle(Vector2D X, Vector2D Y, Vector2D Z,
	Vector2D W, Vector2D P) {
	if (PointInTriangle(X, Y, Z, P))
		return true;
	if (PointInTriangle(X, Z, W, P))
		return true;
	return false;
}

bool Collisions::PointInTriangle(Vector2D A, Vector2D B, Vector2D C,
	Vector2D P) {
	// Compute vectors
	Vector2D v0 = C - A;
	Vector2D v1 = B - A;
	Vector2D v2 = P - A;

	// Compute dot products
	double dot00 = v0 * v0;
	double dot01 = v0 * v1;
	double dot02 = v0 * v2;
	double dot11 = v1 * v1;
	double dot12 = v1 * v2;

	// Compute barycentric coordinates
	double invDenom = 1 / (dot00 * dot11 - dot01 * dot01);
	double u = (dot11 * dot02 - dot01 * dot12) * invDenom;
	double v = (dot00 * dot12 - dot01 * dot02) * invDenom;

	// Check if point is in triangle
	if (u >= 0 && v >= 0 && (u + v) < 1) {
		return true;
	}
	else {
		return false;
	}
}

bool Collisions::collides(Vector2D o1Pos, double o1Width, double o1Height, Vector2D o2Pos, double o2Width, double o2Height) {
	// o1 completely to the left of o2, or vice versa
	if (o1Pos.getX() + o1Width < o2Pos.getX()
		|| o2Pos.getX() + o2Width < o1Pos.getX()) {
		return false;
	}

	// o1 completely to the top of o2, or vice versa
	if (o1Pos.getY() + o1Height < o2Pos.getY()
		|| o2Pos.getY() + o2Height < o1Pos.getY()) {
		return false;
	}

	return true;
}