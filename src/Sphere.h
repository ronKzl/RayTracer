#pragma once
#include <ofMain.h>
#include "Ray.h"

class HitRecord {
public:
	glm::vec3 p;
	glm::vec3 normal;
	double t;
	bool frontFace;
										
	void setFaceNormal(Ray& r, glm::vec3 outwardNormal) {
		//must always be a unit length vector
		outwardNormal = glm::normalize(outwardNormal);
		this->frontFace = glm::dot(r.getDirection(), outwardNormal) < 0;
		this->normal = frontFace ? outwardNormal : -outwardNormal;
	}
};

class Sphere {
public:
	Sphere(glm::vec3 sphereCenter, double sphereRadius);
	bool isHit(Ray& r, double ray_tmin, double ray_tmax, HitRecord& record);
	glm::vec3 center;
	double radius;
};
