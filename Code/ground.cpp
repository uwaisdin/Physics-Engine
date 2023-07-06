#include "ground.h"

ground::ground() : ground_normal(Vector3(0, 1, 0)), ground_level(0) {};

void ground::setGround_normal() {
	this->ground_normal = Vector3(0, 1, 0);
}

Vector3 ground::getGround_normal() {
	return ground_normal;
}

void ground::setGround_level() {
	this->ground_level = 0.0f;
}

float ground::getGround_level() {
	return ground_level;
}