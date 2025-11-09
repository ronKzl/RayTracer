#pragma once
#include "ofMain.h"
// represents a light source point in the world, used for lighting and shadow calculations
class LightSource {
public:
	LightSource(glm::vec3 pos, float specularStrength = 0.5, float ambient = 0.1) : lightPosition(pos),
		specularStrength(specularStrength), ambient(ambient) { }
	
	glm::vec3 lightPosition;
	float ambient;
	float specularStrength;

};