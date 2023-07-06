#include "simulation.h"
#include <iostream>
#include <vector>
using namespace std;

int main()
{
    vector<sphere*> s;
    vector <cube*> c;
    for (int i = 0; i < 2; i++) {
        s.push_back(new sphere());

        cout << "set radius for sphere " << i + 1 << endl;
        float r;
        cin >> r;
        s[i]->setRadius(r);
        cout << "enter position (x, y, z) for sphere " << i + 1 << endl;
        float Px, Py, Pz;
        cin >> Px >> Py >> Pz;
        s[i]->setPosition(Vector3(Px, Py, Pz));
        if (Py < r) {
            return 0;
        }
        cout << "enter acceleration (x, z) for sphere " << i + 1 << endl;
        float Ax, Az;
        cin >> Ax >> Az;
        s[i]->setAcceleration(Vector3(Ax, 9.81, Az));
        cout << "set mass for sphere " << i + 1 << endl;
        float m;
        cin >> m;
        s[i]->setMass(m);
    }
    for (int i = 0; i < 2; i++) {
        c.push_back(new cube());
        cout << "set radius for cube " << i + 1 << endl;
        float Cr;
        cin >> Cr;
        c[i]->setRadius(Cr);
        cout << "enter position (x, y, z) for cube " << i + 1 << endl;
        float c_Px, c_Py, c_Pz;
        cin >> c_Px >> c_Py >> c_Pz;
        c[i]->setPosition(Vector3(c_Px, c_Py, c_Pz));
        if (c_Py < Cr) {
            return 0;
        }
        cout << "enter acceleration (x, z) for cube " << i + 1 << endl;
        float Cx, Cz;
        cin >> Cx >> Cz;
        c[i]->setAcceleration(Vector3(Cx, 9.81, Cz));
        cout << "set mass for cube " << i + 1 << endl;
        float Cm;
        cin >> Cm;
        c[i]->setMass(Cm);
    }
    
    simulation sim;
    for (int i = 0; i < 2; i++) {
        sim.addSphere(*s[i]);
        sim.addCube(*c[i]);
    }
    sim.run_sim();
    sim.~simulation();
}


/*
int main() {
    Vector3 s_pos(0, 5, 0);
    Vector3 s_vel(0, 0, 0);
    Vector3 s_acc(0, 0, 0);
    float s_mass = 5.0f;
    float s_rad = 1.0f;
    sphere s(s_pos, s_vel, s_acc, s_mass, s_rad);
    ground g;
    float timeStep = 0.05f;
    float endTime = 10.0f;

    for (float t = 0; t < endTime; t += timeStep) {

        if (s.detect(g)) {
            s.res(g);
            cout << "COLLISION" << endl;
        }
        s.integrate(timeStep);
        cout << "t = " << t << ", position = (" << s.getPosition().getX()
            << ", " << s.getPosition().getY() << ", "
            << s.getPosition().getZ() << ")" << endl;
    }
}
*/

/*
int main() {
    Vector3 v1(1, 2, 3);
    Vector3 v2(4, 5, 6);
    // magnitude 
    float v1_mag = v1.magnitude();
    float v2_mag = v2.magnitude();
    cout << "Magnitude of v1: " << v1_mag << endl;
    cout << "Magnitude of v2: " << v2_mag << endl;
    // squared magnitude 
    float v1_magsqr = v1.magnitudeSquared();
    float v2_magsqr = v2.magnitudeSquared();
    cout << "Squared magnitude of v1: " << v1_magsqr << endl;
    cout << "Squared magnitude of v2: " << v2_magsqr << endl;
    // normalise 
    Vector3 v1_norm = v1;
    Vector3 v2_norm = v2;
    v1_norm.normalise();
    v2_norm.normalise();
    cout << "Normalised v1: (" << v1_norm.getX() << ", " << v1_norm.getY() 
                               << ", " << v1_norm.getZ() << ")" << endl;
    cout << "Normalised v2: (" << v2_norm.getX() << ", " << v2_norm.getY()
                               << ", " << v2_norm.getZ() << ")" << endl;
    // vector +
    Vector3 v3 = v1 + v2;
    cout << "v1 + v2 = (" << v3.getX() << ", " << v3.getY() << ", " << v3.getZ() << ")" << endl;
    // vector -
    Vector3 v4 = v2 - v1;
    cout << "v2 - v1 = (" << v4.getX() << ", " << v4.getY() << ", " << v4.getZ() << ")" << endl;
    // scalar *
    Vector3 v5 = v1 * 2;
    cout << "v1 * 2 = (" << v5.getX() << ", " << v5.getY() << ", " << v5.getZ() << ")" << endl;
    // scalar /
    Vector3 v6 = v2 / 2;
    cout << "v2 / 2 = (" << v6.getX() << ", " << v6.getY() << ", " << v6.getZ() << ")" << endl;
    //cross product
    Vector3 v7 = v1.cross(v2);
    cout << "v1 x v2 = (" << v7.getX() << ", " << v7.getY() << ", " << v7.getZ() << ")" << endl;
    // dot product
    float dotProduct = v1.dot(v2);
    cout << "v1 . v2 = " << dotProduct << endl;
    // equality 
    Vector3 v8(1, 2, 3);
    if (v1 == v8) {
        cout << "v1 == v8" << endl;
    }
    else {
        cout << "v1 != v8" << endl;
    }
}
*/



/*
int main() {
    Vector3 s_pos1(0, 1, 0);
    Vector3 s_vel1(0, 0, 0);
    Vector3 s_acc1(0, 0, 0);
    float s_mass1 = 5.0;
    float s_rad1 = 1.0;
    sphere s1(s_pos1, s_vel1, s_acc1, s_mass1, s_rad1);

    Vector3 s_pos2(-3, 1.0, 0);
    Vector3 s_vel2(3, 0, 0);
    Vector3 s_acc2(10, 0, 0);
    float s_mass2 = 15.0;
    float s_rad2 = 1.0;
    sphere s2(s_pos2, s_vel2, s_acc2, s_mass2, s_rad2);

    Vector3 ground_normal(0, 1, 0);
    float ground_level = 0.0f;
    float timeStep = 0.01f;
    float endTime = 5.0f;

    for (float t = 0; t < endTime; t += timeStep) {

        if (s1.detect(s2) == 1) {
            s1.res(s2);
            cout << "COLLISION" << endl;
        }
        s1.integrate(timeStep);
        if (s2.detect(s1) == 1) {
            s2.res(s1);
            cout << "COLLISION" << endl;
        }
        s2.integrate(timeStep);
        cout << "t = " << t << ", position 1 = (" << s1.getPosition().getX()
            << ", " << s1.getPosition().getY() << ", "
            << s1.getPosition().getZ() << ")"
            << ", position 2 = (" << s2.getPosition().getX() 
            << ", " << s2.getPosition().getY()
            << ", " << s2.getPosition().getZ() << ")" << endl;
    }
}
*/

/*
int main() {

	point_mass p(Vector3(0, 3, 0), Vector3(0, 0, 0), Vector3(0, 0, 0), 1.0);

	float timeStep = 0.01f;
	float endTime = 0.3f;

	for (float t = 0; t < endTime; t += timeStep) {
		p.integrate(timeStep);

		cout << "t = " << t << ", position = (" << p.getPosition().getX()
			 << ", " << p.getPosition().getY() << ", " << p.getPosition().getZ() << ")" << endl;
	}
}
*/

/*
int main() {

    // create two point masses
    Vector3 pos1(1, 1, 1);
    Vector3 vel1(0, 0, 0);
    Vector3 acc1(0, 0, 0);
    float mass1 = 1;
    point_mass pm1(pos1, vel1, acc1, mass1);

    Vector3 pos2(1, 1, 1);
    Vector3 vel2(0, 0, 0);
    Vector3 acc2(0, 0, 0);
    float mass2 = 1;
    point_mass pm2(pos2, vel2, acc2, mass2);

    // create detector object
    pmDetect detector;

    // test pmDetect::detect(pm1, pm2)
    bool result = detector.detect(pm1, pm2);
    cout << "pmDetect::detect(pm1, pm2) result: " << result << endl;

    // test pmDetect::detect(pm, ground)
    Vector3 pos3(5, 0, 0);
    Vector3 vel3(0, 0, 0);
    Vector3 acc3(0, 0, 0);
    float mass3 = 1;
    point_mass pm3(pos3, vel3, acc3, mass3);

    float ground = 0;
    result = detector.detect(pm3, ground);
    cout << "pmDetect::detect(pm3, ground) result: " << result << endl;

    return 0;
}
*/