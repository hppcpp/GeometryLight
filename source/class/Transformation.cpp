#include "CAP/GLT.hpp"

#include "class/Transformation.h"

Transformation::Transformation() :
	model(glm::mat4(1.0f)),
	position(glm::vec3(0.0f)),
	rotation(glm::vec3(0.0f)),
	scale(glm::vec3(0.0f))
{}

Transformation::Transformation(const glm::vec3& posi, const glm::vec3& rota, const glm::vec3 scal) :
	model(glm::mat4(1.0f)),
	position(posi),
	rotation(rota),
	scale(scal)
{}

void Transformation::formModel()
{
	model = glm::mat4(1.0f);
	model = translate(model, position);
	model = glm::rotate(model, glm::radians(rotation[1]), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::rotate(model, glm::radians(rotation[2]), glm::vec3(0.0f, 1.0f, 0.0f));
	model = glm::rotate(model, glm::radians(rotation[0]), glm::vec3(1.0f, 0.0f, 0.0f));
	model = glm::scale(model, scale);
}
