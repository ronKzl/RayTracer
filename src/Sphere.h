#pragma once
#include <ofMain.h>
#include "Ray.h"

// adopted from Shirley's book, holds all the relevant info about the closest point hit
class HitRecord {
public:
	glm::vec3 pointColision; // the exact colission point in the world
	glm::vec3 normal; // surface normal
	double t; // discriminant vector
	bool frontFace;
	glm::vec3 objectAlbedo; // sphere color for diffuse and ambient
	float highlightStrengh; // sphere highlight strength for specular
	float shininess; // sphere surface shininess for specular
	
	/*
	Helper sets the proper surface normal vector, will always point against the ray
	*/
	void setFaceNormal(Ray& r, glm::vec3 outwardNormal) {
		// must always be a unit length vector
		outwardNormal = glm::normalize(outwardNormal);
		// store info if ray is inside (false) or outside the spehre (true)
		this->frontFace = glm::dot(r.getDirection(), outwardNormal) < 0;
		this->normal = frontFace ? outwardNormal : -outwardNormal;
	}
};

/*
Sphere class that holds all the relevant info for sphere raycasting calculations
*/
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
