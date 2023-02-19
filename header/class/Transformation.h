#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Transformation
{
protected:
	glm::mat4 model;
	glm::vec3 position, rotation, scale;

public:
	Transformation();
	explicit Transformation(const glm::vec3&, const glm::vec3&, const glm::vec3 scal=glm::vec3(1.0f));
	virtual ~Transformation() {}

	void formModel();

	const glm::mat4& getModel()const { return model; }
	glm::mat4& setModel() { return model; }
	const glm::vec3& getPosition()const { return position; }
	const glm::vec3& getRotation()const { return rotation; }
	const glm::vec3& getScale()const { return scale; }
	glm::vec3& setPosition() { return position; }
	glm::vec3& setRotation() { return rotation; }
	glm::vec3& setScale() { return scale; }
};
