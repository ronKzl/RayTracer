#pragma once

#include "ofMain.h"

//for now here maybe later have its own class file
class Ray {
public:
    Ray() {}
    Ray(const glm::vec3& origin, const glm::vec3& direction) : origin(origin), direction(direction) {}

    glm::vec3 origin; 
    glm::vec3 direction; 

    //give immutable reference
    const glm::vec3& getOrigin() const { return origin; }
    const glm::vec3& getDirection() const { return direction; }

    glm::vec3 at(double t) {
        return origin + (direction * t);
    }
};

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		

        

        // Output
        ofImage renderImg;

        ofFloatColor ray_color(const Ray& r);

        
};
