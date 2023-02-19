#pragma once

#include "Line.h"

class Ray :public Line
{
public:
	explicit Ray(double, int, const glm::vec3&, const glm::vec3&, const glm::vec4&,
		const glm::vec3& posi = glm::vec3(0.0f), const glm::vec3& rota = glm::vec3(0.0f), const glm::vec3& sca = glm::vec3(1.0f));
};
