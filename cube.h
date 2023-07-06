#pragma once
#include "sphere.h"
#include <vector>

using namespace std;

class cube : public point_mass {
private:
    float radius;
    float length;
    vector<Vector3> normals{};

public:
    /* constructor */
    cube();
    cube(Vector3 p, Vector3 v, Vector3 a, float m, float r, float l);

    /* setters and getters */
    void setRadius(float r);
    float getRadius();
    void setreference();

    /* collisions */
    /* detection between cube and ground */
    bool detect(ground g);
    /* detection between two cubes */
    bool detect(cube& s2);
    /* detection between a cube and a sphere*/
    bool detect(sphere& s2);
    /* resolution between cube and ground */
    void res(ground g);
    /* resolution between cube and sphere */
    void res(sphere& s2);
    /* resolution between two cubes */
    void res(cube& c2);

    /* integrate eulers method */
    void integrate(float time);
};