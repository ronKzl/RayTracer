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
		glm::vec3 cameraCenter = glm::vec3(0, 0, 10);
		const double infinity = std::numeric_limits<double>::infinity();
		const float aspectRatio = 16.0 / 9.0;
		const int imageWidth = 1024;
		const float focalLength = 2.0;
		const float viewportHeight = 2.0;


		std::vector<Sphere> spheres;
		std::vector<LightSource> lightSources;
		HitRecord persistantRecord;
        // Output
        ofImage renderImg;

		glm::vec3 ray_color( Ray& r);
		glm::vec3 calcThreePointLight(HitRecord& record);
  
};
