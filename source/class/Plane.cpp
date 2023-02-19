#include "class/Plane.h"
#include "function/universal.h"

Plane::Plane() :
	isMaterial(false)
{
	memset(&material, 0, sizeof(material));
}
Plane::Plane(const glm::vec3& posi, const glm::vec3& rota, const glm::vec3& sca,
	int shad, const glm::vec4& col,
	bool isMate, float shininess, const char* const diffusePath, const char* const specularPath) :
	Geometry(posi, rota, sca, shad, col),
	isMaterial(isMate)
{
	material.shininess = shininess;
	material.diffuse = textureFile(diffusePath);
	material.specular = textureFile(specularPath);
}
Plane::~Plane()
{
	glDeleteTextures(1, &material.diffuse);
	glDeleteTextures(1, &material.specular);
}
