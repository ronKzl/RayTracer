#pragma once
#include "ofMain.h"

class LightSource {
public:
	LightSource(glm::vec3 pos, float specularStrength = 0.5, float ambient = 0.1);
	
	glm::vec3 lightPosition;
	float ambient;
	float specularStrength;

};