#include "sphere.h"

sphere::sphere() : point_mass(), radius(0.0f) {}

sphere::sphere(Vector3 p, Vector3 v, Vector3 a, float m, float r) : 
   point_mass(p, v, a, m), radius(r) {}

void sphere::setRadius(float r) {
    this->radius = r;
}
float sphere::getRadius() {
    return radius;
}

bool sphere::detect(ground g) {

	// if sphere is touching ground detection
	float d = position.getY() - g.getGround_level();
	return(d <= radius);
}

bool sphere::detect(sphere& s2) {
	// if spheres are touching detection
	Vector3 s2Pos = s2.getPosition();
	float r2 = s2.getRadius();
	Vector3 d = position - s2Pos;
	float d_mag = d.magnitude();
	return (d_mag <= radius + r2);
}


void sphere::res(ground g) {
	
	/* splits into parallel and perpendicular components and	
	changes perpendulcar component reduces perpendicular component */

	Vector3 gn = g.getGround_normal();

	Vector3 velPerp = velocity; 
	velPerp.dot(gn);	// vertical velocity 
	Vector3 s_velParallel = velocity - velPerp; // horizontal velocity
	velPerp = velPerp * (-0.5f); // energy loss constant
	Vector3 set = velPerp + s_velParallel;
	velocity = set;	
}

void sphere::res(sphere& s2) {

	Vector3 unit_vec = s2.getPosition() - position;
	unit_vec.normalise(); // unit vector at point of collision
    Vector3 velBetween = s2.getVelocity() - velocity; //  velocity between two spheres
    float vel = velBetween.dot(unit_vec); // mag of velocity perp to collision unit vector

    if (vel > 0) { 
       return;	// spheres are moving away no collisiomn
    }

    float impulse_mag =  -(0.5f * vel) * s2.getMass(); //0.5 is energy loss p=mv

    // update spheres velocity using impulse 
    Vector3 impulse = unit_vec * impulse_mag; // impulse as a vector using unit vector
	Vector3 v1_lost = impulse / mass;	// p=mv
    velocity -= v1_lost; // being slowed down by other sphere
	Vector3 v2_gained = impulse / s2.getMass(); // p=mv
    s2.setVelocity(s2.getVelocity() + v2_gained); // being pushed 
}

void sphere::integrate(float time) {

	ground g;
	// if on floor stop accelerating downwards
	if ((position.getY() - radius) <= g.getGround_level()) {
		acceleration.setY(0);
	}
	// gravity 
	else {
		acceleration.setY(-9.81f);	
	}

	// eulers method

	Vector3 at = acceleration * time;
	velocity += at;
	Vector3 vt = velocity * time;
	position += vt;

}