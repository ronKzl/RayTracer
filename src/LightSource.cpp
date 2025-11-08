#include "LightSource.h"

LightSource::LightSource(glm::vec3 pos, float specularStrength, float ambient): lightPosition(pos),
specularStrength(specularStrength), ambient(ambient) { }