#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "CAP/GLT.hpp"

#include "class/Line.h"
#include "static.hpp"

Line::Line() :
	endpoint{ glm::vec3(0.0f),glm::vec3(0.0f) }
{}
Line::Line(int shad, const glm::vec4& col,
	const glm::vec3& point1, const glm::vec3& point2,
	const glm::vec3& posi, const glm::vec3& rota, const glm::vec3& sca) :
	Geometry(posi, rota, sca, shad, col),
	endpoint{ point1,point2 }
{
	generate();
}
Line::~Line()
{
	glDeleteVertexArrays(1, &vertexArray);
}

void Line::bindBufferArray()const
{
	float vertices[] =
	{
		endpoint[0][0],endpoint[0][1],endpoint[0][2],
		endpoint[1][0],endpoint[1][1],endpoint[1][2],
	};

	CAP::GLSL::bindBufferData(GL_ARRAY_BUFFER, vertexBuffer, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	glBindVertexArray(vertexArray);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(glm::vec3), reinterpret_cast<void*>(NULL));
}
void Line::draw()const
{
	ShaderProgram& shaderPg = initShader();

	glBindVertexArray(vertexArray);
	glDrawArrays(GL_LINES, 0, 2);
}
