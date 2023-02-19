#pragma once

#include <windows.h>

#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "class/Geometry.h"

class Line: public Geometry
{
protected:
	glm::vec3 endpoint[2];
public:
	Line();
	explicit Line(int, const glm::vec4&,
		const glm::vec3&, const glm::vec3&,
		const glm::vec3& posi = glm::vec3(0.0f), const glm::vec3& rota = glm::vec3(0.0f), const glm::vec3& sca = glm::vec3(1.0f));
	virtual ~Line();

	void bindBufferArray()const;
	void draw()const;
	
	const glm::vec3* getPVertex()const { return endpoint; }
	glm::vec3* setPVertex() { return endpoint; }
	const glm::vec4& getColor()const { return color; }
	glm::vec4& setColor() { return color; }
};
