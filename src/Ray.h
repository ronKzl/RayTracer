#pragma once
#include "ofMain.h"
//for now here maybe here - from shirley adapted to oF Ray class
class Ray {
public:
    Ray() {}
    Ray(const glm::vec3& origin, const glm::vec3& direction) : origin(origin), direction(direction) {}

    //double hitSphere(Sphere* s) {
    //    glm::vec3 oc = s->center - this->origin;
    //    auto a = glm::length2(this->direction);
    //    auto h = glm::dot(this->direction, oc);
    //    auto c = glm::length2(oc) - pow(s->radius, 2);
    //    auto discriminant = pow(h, 2) - (a * c);
    //    /*auto a = glm::dot(this->direction, this->direction);
    //    auto b = -2.0 * glm::dot(this->direction, oc);
    //    auto c = glm::dot(oc, oc) - pow(s->radius, 2);
    //    auto discriminant = pow(b, 2) - 4 * a * c;*/

    //    if (discriminant <= 0) {
    //        return -1.0;
    //    }
    //    else {
    //        //return (-b - std::sqrt(discriminant)) / (2.0 * a);
    //        return (h - std::sqrt(discriminant)) / a;
    //    }
    //}
    glm::vec3 origin;
    glm::vec3 direction;

    //give immutable reference
    const glm::vec3& getOrigin() const { return origin; }
    const glm::vec3& getDirection() const { return direction; }

    glm::vec3 at(double t) {
        return origin + (direction * t);
    }
};