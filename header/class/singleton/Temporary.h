#pragma once

#include "class/Cuboid.h"
#include "class/Orthogon.h"
#include "struct/DirLight.h"
#include "struct/PointLight.h"
#include "struct/SpotLight.h"

class Temporary
{
private:
	Temporary() {}
	Temporary(const Temporary&) {}
	Temporary& operator=(const Temporary&) {}
	~Temporary() {}
protected:
public:
	static Temporary& singleton()
	{
		static Temporary value;
		return value;
	}
	


	Cuboid* container, * pointLightBox, * spotLightBox;
	DirLight dirLight;
	Orthogon* bricks;
	PointLight pointLight;
	SpotLight spotLight;
	glm::vec3 ambient;
};
