#pragma once
#include "ofMain.h"
// adopted from Shirley's book, represents the ray in the world space
class Ray {
public:
    Ray() {}
    Ray(const glm::vec3& origin, const glm::vec3& direction) : origin(origin), direction(direction) {}

    glm::vec3 origin;
    glm::vec3 direction;

    const glm::vec3& getOrigin() const { return origin; }
    const glm::vec3& getDirection() const { return direction; }

    glm::vec3 at(double t) {
        return origin + (direction * t); // Q + dt
    }
};