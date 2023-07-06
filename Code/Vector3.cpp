#include "Vector3.h"
#include <cmath>

using namespace std;

/* constructors */
Vector3::Vector3() : x_(0), y_(0), z_(0) {}
Vector3::Vector3(float x, float y, float z) : x_(x), y_(y), z_(z) {}


/* setters and getters */
void Vector3::setX(float x) {
	this->x_ = x;
}

float Vector3::getX() {
	return x_;
}

void Vector3::setY(float y) {
	this->y_ = y;
}

float Vector3::getY() {
	return y_;
}

void Vector3::setZ(float z) {
	this->z_ = z;
}

float Vector3::getZ() {
	return z_;
}


/* calculations */

/*calculates magnitude of vector */
float Vector3::magnitude() {

	return float(pow(x_ * x_ + y_ * y_ + z_ * z_, 0.5));
}
/*calculates sqaured magnitude of vector */
float Vector3::magnitudeSquared() {

	return (x_ * x_ + y_ * y_ + z_ * z_);
}
/* normalises Vector */
void Vector3::normalise() {

	float m = magnitude();
	if (m != 0) {

		x_ /= m;
		y_ /= m;
		z_ /= m;
	}

}
/* operator overloading */
Vector3 Vector3::operator+(Vector3& other) {
	Vector3 v(x_ + other.x_, y_ + other.y_, z_ + other.z_);
	return v;
}
void Vector3::operator+=(Vector3& other) {
	x_ += other.x_;
	y_ += other.y_;
	z_ += other.z_;
}
Vector3 Vector3::operator-(Vector3& other) {
	Vector3 v(x_ - other.x_, y_ - other.y_, z_ - other.z_);
	return v;
}
void Vector3::operator-=(Vector3& other) {
	x_ -= other.x_;
	y_ -= other.y_;
	z_ -= other.z_;
}
/* scalar multiplication*/
Vector3 Vector3::operator*(float scalar) {
	Vector3 v(x_ * scalar, y_ * scalar, z_ * scalar);
	return v;
}
/* scalar division*/
Vector3 Vector3::operator/(float scalar) {
	Vector3 v(x_ / scalar, y_ / scalar, z_ / scalar);
	return v;
}
bool Vector3::operator==(Vector3& other) {
	return (x_ == other.x_) && (y_ == other.y_) && (z_ == other.z_);
}
/* cross product*/
Vector3 Vector3::cross(Vector3& other) {
	float x = y_ * other.z_ - z_ * other.y_;
	float y = z_ * other.x_ - x_ * other.z_;
	float z = x_ * other.y_ - y_ * other.x_;
	return Vector3(x, y, z);
}
/* dot prodcut */
float Vector3::dot(Vector3& other) {
	float x = x_ * other.x_ + y_ * other.y_ + z_ * other.z_;
	return x;
}
