#pragma once

#include <glm/glm.hpp>

#include "Reflection.h"

struct SpotLight
{
	float compensation;
	glm::vec2 cutoff;
	glm::vec3 attenuation;
	glm::vec3 direction;
	glm::vec3 position;

	struct Reflection reflection;
};
