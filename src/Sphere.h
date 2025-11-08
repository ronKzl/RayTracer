#pragma once
#include <ofMain.h>
#include "Ray.h"

//adopted from Shirley's book, holds all the revlant info about the closest object hit
class HitRecord {
public:
	glm::vec3 pointColision;
	glm::vec3 normal; 
	double t;
	bool frontFace;
	glm::vec3 objectAlbedo;
	float highlightStrengh;
	float shininess;
										
	void setFaceNormal(Ray& r, glm::vec3 outwardNormal) {
		//must always be a unit length vector
		outwardNormal = glm::normalize(outwardNormal);
		this->frontFace = glm::dot(r.getDirection(), outwardNormal) < 0;
		this->normal = frontFace ? outwardNormal : -outwardNormal;
	}
};

class Sphere {
public:
	Sphere(glm::vec3 sphereCenter, double sphereRadius, glm::vec3 color = glm::vec3(0.3,0.6,0.5), float highlights = 1.0, float shininess = 0.0);
	bool isHit(Ray& r, double ray_tmin, double ray_tmax, HitRecord& record);
	glm::vec3 center;
	double radius;
	glm::vec3 albedo;
	float highlights;
	float shininess;
};
