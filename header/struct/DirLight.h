#pragma once

#include <glm/glm.hpp>

#include "Reflection.h"

struct DirLight
{
	glm::vec3 direction;

	struct Reflection reflection;
};
