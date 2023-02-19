#pragma once

#include <glm/glm.hpp>

#include "Reflection.h"

struct PointLight
{
	float compensation;
	glm::vec3 attenuation;
	glm::vec3 position;

	struct Reflection reflection;
};
