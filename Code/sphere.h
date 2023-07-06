#pragma once
#include "point_mass.h"

class sphere : public point_mass {
private:
	float radius;
public:
	/* constructor */
	sphere();
	sphere(Vector3 p, Vector3 v, Vector3 a, float m, float r);

    /* setters and getters */
	void setRadius(float r);
    float getRadius();

	/* collisions */
	/* detection between sphere and ground */
	bool detect(ground g);
	/* detection between two spheres */
	bool detect(sphere& s2);
	/* resolution between sphere and ground */
	void res(ground g);
	/* resolution between two spheres */
	void res(sphere& s2);

	/* integrate eulers method */
	void integrate(float time);
};