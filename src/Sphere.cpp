#include "Sphere.h"

Sphere::Sphere(glm::vec3 sphereCenter, double sphereRadius): center(sphereCenter), radius(sphereRadius) {}


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

	//find nearest rood that lies in the range
	auto root = (h - sqrtd) / a;
	if (root <= ray_tmin || root >= ray_tmax) {
		root = (h + sqrtd) / a;
		if (root <= ray_tmin || root >= ray_tmax) {
			return false;
		}
	}

	
	record.t = root;
	record.p = r.at(record.t);
	glm::vec3 outwardNormal = (record.p - this->center) / this->radius;
	record.setFaceNormal(r, outwardNormal);


	return true;
}