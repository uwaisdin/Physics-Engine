#pragma once
#include <cmath>

using namespace std;

/* 3D Vector Class defines area in space */

class Vector3 {

private: 
	/* x, y and z coordiantes */
	float x_;
	float y_;
	float z_;
public:
	/* constructors */
	Vector3();
	Vector3(float x, float y, float z);

	/* setters and getters */
	void setX(float x);
	float getX();
	void setY(float y);
	float getY();
	void setZ(float z);
	float getZ();

	/* calculations */
	float magnitude();
	float magnitudeSquared();
	void normalise();
	Vector3 operator+(Vector3& other);
	void operator+=(Vector3& other);
	Vector3 operator-(Vector3& other);
	void operator-=(Vector3& other);
	bool operator==(Vector3& other);
	Vector3 operator*(float scalar); 
	Vector3 operator/(float scalar); 
	Vector3 cross(Vector3& other);
	float dot(Vector3& other);
};