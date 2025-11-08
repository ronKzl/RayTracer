#pragma once

#include "ofMain.h"
#include "Sphere.h"
#include "LightSource.h"
#include "math.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void draw();

		
		glm::vec3 camera_center = glm::vec3(0, 0, 10);
		const double infinity = std::numeric_limits<double>::infinity();
		std::vector<Sphere> spheres;
		std::vector<LightSource> lightSources;
		HitRecord persistantRecord;
        // Output
        ofImage renderImg;

		glm::vec3 ray_color( Ray& r);

		glm::vec3 calcThreePointLight(HitRecord& record);
  
};
