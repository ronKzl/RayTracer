#pragma once

#include "ofMain.h"
#include "Sphere.h"
#include "LightSource.h"
#include "math.h"

class ofApp : public ofBaseApp{

	public:
		void setup();
		void draw();

		// constants for calculating screen and camera position
		glm::vec3 camera_center = glm::vec3(0, 0, 10);
		const double infinity = std::numeric_limits<double>::infinity();
		const float aspect_ratio = 16.0 / 9.0;
		const int image_width = 1024;
		const float focal_length = 2.0;
		const float viewport_height = 2.0;


		std::vector<Sphere> spheres;
		std::vector<LightSource> lightSources;
		HitRecord persistantRecord;
        // Output
        ofImage renderImg;

		glm::vec3 ray_color( Ray& r);
		glm::vec3 calcThreePointLight(HitRecord& record);
  
};
