#pragma once
#include "Vector3.h"

using namespace std;

class ground {
private:
	 Vector3 ground_normal;
	 float ground_level;
public:
	ground();
	void setGround_normal();
	Vector3 getGround_normal();
	void setGround_level();
	float getGround_level();
};
