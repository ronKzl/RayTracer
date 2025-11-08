#include "Sphere.h"

Sphere::Sphere(glm::vec3 sphereCenter, double sphereRadius, glm::vec3 color, float highlights): center(sphereCenter), 
radius(sphereRadius), albedo(color), highlights(highlights) {}

//main logic from Shirley's book
bool Sphere::isHit(Ray& r, double ray_tmin, double ray_tmax, HitRecord& record) {
	glm::vec3 oc = this->center - r.getOrigin();
	auto a = glm::length2(r.getDirection());
	auto h = glm::dot(r.getDirection(), oc);
	auto c = glm::length2(oc) - pow(this->radius, 2);

	auto discriminant = pow(h, 2) - (a * c);
	if (discriminant <= 0.0) {
		return false;
	}

	auto sqrtd = std::sqrt(discriminant);

	//smallest t test
	auto root = (h - sqrtd) / a;
	if (root <= ray_tmin || root >= ray_tmax) {
		root = (h + sqrtd) / a;
		if (root <= ray_tmin || root >= ray_tmax) {
			return false;
		}
	}

	
	record.t = root;
	record.pointColision = r.at(record.t);
	record.objectAlbedo = this->albedo;
	record.highlightStrengh = this->highlights;
	glm::vec3 outwardNormal = (record.pointColision - this->center) / this->radius;
	record.setFaceNormal(r, outwardNormal);


	return true;
}