#pragma once

#include "ofMain.h"
#include "Sphere.h"
#include "math.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void update();
		void draw();

		void keyPressed(int key);
		

        
		const double infinity = std::numeric_limits<double>::infinity();
		std::vector<Sphere> spheres;
		HitRecord persistantRecord;
        // Output
        ofImage renderImg;

		glm::vec3 ray_color( Ray& r);

        
};
