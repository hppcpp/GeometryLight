#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "CAP/GLSL/shader.hpp"

#include "class/FrameVertex.h"

FrameVertex::FrameVertex() :
	vertexArray(0),
	vertexBuffer(0)
{
	generate();
	bindBufferArray();
}
FrameVertex::~FrameVertex()
{
	expurgate();
}

void FrameVertex::bindBufferArray()const
{
	float vertices[] =
	{
		-1,-1,	0,0,
		1,-1,	1,0,
		1,1,	1,1,
		1,1,	1,1,
		-1,1,	0,1,
		-1,-1,	0,0,
	};

	CAP::GLSL::bindBufferData(GL_ARRAY_BUFFER, vertexBuffer, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(vertexArray);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), reinterpret_cast<void*>(NULL));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), reinterpret_cast<void*>(2 * sizeof(float)));
}
void FrameVertex::expurgate()
{
	glDeleteBuffers(1, &vertexBuffer);

	glDeleteVertexArrays(1, &vertexArray);
}
void FrameVertex::generate()
{
	glGenBuffers(1, &vertexBuffer);

	glGenVertexArrays(1, &vertexArray);
}
