#pragma once

#include "class/Geometry.h"

class Plane : public Geometry
{
protected:
	bool isMaterial;
	Material material;
public:
	Plane();
	explicit Plane(const glm::vec3&, const glm::vec3&, const glm::vec3&,
		int, const glm::vec4&,
		bool isMate = false, float shininess = 0, const char* const diffusePath = 0, const char* const specularPath = 0);
	~Plane();

	bool getIsMaterial()const { return isMaterial; }
	void setIsMaterial(bool value) { isMaterial = value; }
	const Material& getMaterial()const { return material; }
	Material& setMaterial() { return material; }
};
