#include "cube.h"

using namespace std;

cube::cube() : point_mass(), radius(0.0f), length(0.0f) {
    setreference();
}

cube::cube(Vector3 p, Vector3 v, Vector3 a, float m, float r, float l) :
    point_mass(p, v, a, m), radius(r), length(l) {
    setreference();
}
void cube::setRadius(float r) {
    this->radius = r;
    length = r / 1.732f;
}
float cube::getRadius() {
    return radius;
}

void cube::setreference() {
    const Vector3 ndefinition[6] = { Vector3(1,0,0),Vector3(-1,0,0),Vector3(0,1,0),
          Vector3(0,-1,0),Vector3(0,0,1),Vector3(0,0,-1) };

    for (int i = 0; i < 6; i++) {
        normals.push_back(ndefinition[i]);
    }

}

bool cube::detect(ground g) {

    // if cube is touching ground detection
    //since orientation will always in -z normal, so use radius from -z normal (0,0,-1)
    float d = position.getY() - g.getGround_level();
    return(d <= length / 2);
}

bool cube::detect(sphere& s2) {
    // if cubes are touching detection
    Vector3 s2Pos = s2.getPosition();
    float r2 = s2.getRadius();
    Vector3 d = position - s2Pos;

    Vector3 d_dir = d;
    d_dir.normalise();

    float colr = 0; // collision radius

    for (int i = 0; i < 6; i++) {
        float ndot = normals[i].dot(d_dir);
        if (ndot >= 0.5) {
            colr = length / 2;
        }
        else if (ndot < 0.5) {
            colr = radius;
        }
    }


    float d_mag = d.magnitude();
    return (d_mag <= colr + r2);
}

bool cube::detect(cube& c2) {
    // if cubes are touching detection
    Vector3 c2Pos = c2.getPosition();
    float r2 = c2.getRadius();
    Vector3 d = position - c2Pos;

    Vector3 d_dir = d;
    d_dir.normalise();

    float colr = 0; // collision radius

    for (int i = 0; i < 6; i++) {
        float ndot = normals[i].dot(d_dir);
        if (ndot >= 0.5) {
            colr = length / 2;
        }
        else if (ndot < 0.5) {
            colr = radius;
        }
    }

    float d_mag = d.magnitude();
    return (d_mag <= colr + r2);
}


void cube::res(ground g) {

    /* splits into parallel and perpindicular components
    and    changes perpindulcar component reduces perpindicular component */
    Vector3 gn = g.getGround_normal();
    Vector3 velPerp = velocity;
    velPerp.dot(gn);    // vertical velocity
    Vector3 s_velParallel = velocity - velPerp; // horizontal velocity
    velPerp = velPerp * (-0.5f); // energy loss constant
    Vector3 set = velPerp + s_velParallel;
    velocity = set;
}

void cube::res(sphere& s2) {

    Vector3 unit_vec = s2.getPosition() - position;
    unit_vec.normalise(); // unit vector at point of collision
    Vector3 velBetween = s2.getVelocity() - velocity; // calculate velocity between two cubes
    float vel = velBetween.dot(unit_vec); // mag of velocity perpindicular to collision unit vector

    if (vel > 0) {
        return;    // cubes are moving away no collisiomn
    }

    float impulse_mag = -(0.5f * vel) * s2.getMass(); //0.5 is energy loss p=mv

    // update cubes velocity using impulse
    Vector3 impulse = unit_vec * impulse_mag; // impulse as a vector using unit vector
    Vector3 v1_lost = impulse / mass;    // p=mv
    velocity -= v1_lost; // being slowed down by other cube
    Vector3 v2_gained = impulse / s2.getMass(); // p=mv
    s2.setVelocity(s2.getVelocity() + v2_gained); // being pushed
}

void cube::res(cube& c2) {

    Vector3 unit_vec = c2.getPosition() - position;
    unit_vec.normalise(); // unit vector at point of collision
    Vector3 velBetween = c2.getVelocity() - velocity; // calculate velocity between two cubes
    float vel = velBetween.dot(unit_vec); // mag of velocity perpindicular to collision unit vector

    if (vel > 0) {
        return;    // cubes are moving away no collisiomn
    }

    float impulse_mag = -(0.5f * vel) * c2.getMass(); //0.5 is energy loss p=mv

    // update cubes velocity using impulse
    Vector3 impulse = unit_vec * impulse_mag; // impulse as a vector using unit vector
    Vector3 v1_lost = impulse / mass;    // p=mv
    velocity -= v1_lost; // being slowed down by other cube
    Vector3 v2_gained = impulse / c2.getMass(); // p=mv
    c2.setVelocity(c2.getVelocity() + v2_gained); // being pushed
}

void cube::integrate(float time) {

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
