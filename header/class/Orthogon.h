#pragma once

#include "class/Plane.h"

class Orthogon :public Plane
{
protected:
	glm::vec2 pOrthogon;
public:
	Orthogon();
	explicit Orthogon(const glm::vec3&, const glm::vec3&, const glm::vec3&,
		int, const glm::vec4&,
		const glm::vec2&,
		bool isMate = false, float shininess = 0, const char* const diffusePath = 0, const char* const specularPath = 0);

	void bindBufferArray()const;
	void draw()const;
	void update();

	const glm::vec2& getPOrthogon()const { return pOrthogon; }
	glm::vec2& setPOrthogon() { return pOrthogon; }
};
