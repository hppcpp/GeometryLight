#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "class/Geometry.h"
#include "class/Singleton/Setting.h"
#include "function/universal.h"
#include "static.hpp"

Geometry::Geometry() :
	isOver(false),
	vertexArray(0),
	vertexBuffer(0),
	shading(0),
	color(glm::vec4(0.0f))
{}
Geometry::Geometry(const glm::vec3& posi, const glm::vec3& rota, const glm::vec3& sca,
		int shad, const glm::vec4& col) :
	Transformation(posi, rota, sca),
	isOver(false),
	vertexArray(0),
	vertexBuffer(0),
	shading(shad),
	color(col)
{
	generate();
}
Geometry::~Geometry()
{
	expurgate();
}

void Geometry::expurgate()
{
	glDeleteBuffers(1, &vertexBuffer);

	glDeleteVertexArrays(1, &vertexArray);
}
void Geometry::generate()
{
	glGenBuffers(1, &vertexBuffer);

	glGenVertexArrays(1, &vertexArray);
}
void Geometry::updateShading()
{
	shading = Setting::singleton().shading;
}
ShaderProgram& Geometry::initShader()const
{
	ShaderProgram& shaderPg = shaderProgramMap()[shading];
	shaderPg.getProgram().use();

	shaderPg.getProgram().setUniformMat4f("projection", &Global::singleton().projection[0][0]);
	shaderPg.getProgram().setUniformMat4f("view", &Global::singleton().view[0][0]);
	shaderPg.getProgram().setUniformMat4f("model", &model[0][0]);

	shaderPg.getProgram().setUniform4f("color", &color[0]);

	return shaderPg;
}
