#pragma once

#include "class/Plane.h"

class Cuboid :public Plane
{
protected:
	glm::vec3 pCuboid;
public:
	Cuboid();
	explicit Cuboid(const glm::vec3&, const glm::vec3&, const glm::vec3&, 
		int, const glm::vec4&,
		const glm::vec3&,
		bool isMate = false, float shininess = 0, const char* const diffusePath = 0, const char* const specularPath = 0);

	void bindBufferArray()const;
	void draw()const;
	void update();

	const glm::vec3& getPCuboid()const { return pCuboid; }
	glm::vec3& setPCuboid() { return pCuboid; }
};
