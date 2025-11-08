#pragma once
#include <ofMain.h>

class Sphere {
public:
	Sphere(glm::vec3 sphereCenter, double sphereRadius);

	glm::vec3 center;
	double radius;
};
