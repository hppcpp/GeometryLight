#include "class/Cuboid.h"
#include "class/ShaderProgram.h"
#include "static.hpp"
#include "struct/Vertex.h"

Cuboid::Cuboid() :
	pCuboid(glm::vec3(0.0f))
{}
Cuboid::Cuboid(const glm::vec3& posi, const glm::vec3& rota, const glm::vec3& sca,
	int shad, const glm::vec4& col,
	const glm::vec3& point,
	bool isMate, float shininess, const char* const diffusePath, const char* const specularPath) :
	Plane(posi, rota, sca,
		shad, col,
		isMate, shininess, diffusePath, specularPath),
	pCuboid(point)
{}

void Cuboid::bindBufferArray()const
{
	float vertices[] =
	{
		pCuboid[0],-pCuboid[1],-pCuboid[2],		1,0,0,	0,0,
		pCuboid[0],pCuboid[1],-pCuboid[2],		1,0,0,	1,0,
		pCuboid[0],pCuboid[1],pCuboid[2],		1,0,0,	1,1,
		pCuboid[0],pCuboid[1],pCuboid[2],		1,0,0,	1,1,
		pCuboid[0],-pCuboid[1],pCuboid[2],		1,0,0,	0,1,
		pCuboid[0],-pCuboid[1],-pCuboid[2],		1,0,0,	0,0,

		-pCuboid[0],pCuboid[1],-pCuboid[2],		-1,0,0,	0,0,
		-pCuboid[0],-pCuboid[1],-pCuboid[2],	-1,0,0,	1,0,
		-pCuboid[0],-pCuboid[1],pCuboid[2],		-1,0,0,	1,1,
		-pCuboid[0],-pCuboid[1],pCuboid[2],		-1,0,0,	1,1,
		-pCuboid[0],pCuboid[1],pCuboid[2],		-1,0,0,	0,1,
		-pCuboid[0],pCuboid[1],-pCuboid[2],		-1,0,0,	0,0,

		pCuboid[0],pCuboid[1],-pCuboid[2],		0,1,0,	0,0,
		-pCuboid[0],pCuboid[1],-pCuboid[2],		0,1,0,	1,0,
		-pCuboid[0],pCuboid[1],pCuboid[2],		0,1,0,	1,1,
		-pCuboid[0],pCuboid[1],pCuboid[2],		0,1,0,	1,1,
		pCuboid[0],pCuboid[1],pCuboid[2],		0,1,0,	0,1,
		pCuboid[0],pCuboid[1],-pCuboid[2],		0,1,0,	0,0,

		-pCuboid[0],-pCuboid[1],-pCuboid[2],	0,-1,0,	0,0,
		pCuboid[0],-pCuboid[1],-pCuboid[2],		0,-1,0,	1,0,
		pCuboid[0],-pCuboid[1],pCuboid[2],		0,-1,0,	1,1,
		pCuboid[0],-pCuboid[1],pCuboid[2],		0,-1,0,	1,1,
		-pCuboid[0],-pCuboid[1],pCuboid[2],		0,-1,0,	0,1,
		-pCuboid[0],-pCuboid[1],-pCuboid[2],	0,-1,0,	0,0,

		-pCuboid[0],-pCuboid[1],pCuboid[2],		0,0,1,	0,0,
		pCuboid[0],-pCuboid[1],pCuboid[2],		0,0,1,	1,0,
		pCuboid[0],pCuboid[1],pCuboid[2],		0,0,1,	1,1,
		pCuboid[0],pCuboid[1],pCuboid[2],		0,0,1,	1,1,
		-pCuboid[0],pCuboid[1],pCuboid[2],		0,0,1,	0,1,
		-pCuboid[0],-pCuboid[1],pCuboid[2],		0,0,1,	0,0,

		-pCuboid[0],pCuboid[1],-pCuboid[2],		0,0,-1,	0,0,
		pCuboid[0],pCuboid[1],-pCuboid[2],		0,0,-1,	1,0,
		pCuboid[0],-pCuboid[1],-pCuboid[2],		0,0,-1,	1,1,
		pCuboid[0],-pCuboid[1],-pCuboid[2],		0,0,-1,	1,1,
		-pCuboid[0],-pCuboid[1],-pCuboid[2],	0,0,-1,	0,1,
		-pCuboid[0],pCuboid[1],-pCuboid[2],		0,0,-1,	0,0,
	};
	
	CAP::GLSL::bindBufferData(GL_ARRAY_BUFFER, vertexBuffer, sizeof(vertices), &vertices, GL_STATIC_DRAW);

	glBindVertexArray(vertexArray);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(NULL));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, normal)));
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), reinterpret_cast<void*>(offsetof(Vertex, texCoord)));
}
void Cuboid::draw()const
{
	ShaderProgram& shaderPg = initShader();

	shaderPg.getProgram().setUniform1i("isMaterial", isMaterial);

	shaderPg.getProgram().setUniform1f("material.shininess", material.shininess);
	CAP::GLSL::activeBindTexture(0, GL_TEXTURE_2D, material.diffuse);
	shaderPg.getProgram().setUniform1i("material.diffuse", 0);
	CAP::GLSL::activeBindTexture(1, GL_TEXTURE_2D, material.specular);
	shaderPg.getProgram().setUniform1i("material.specular", 1);

	glBindVertexArray(vertexArray);
	glDrawArrays(GL_TRIANGLES, 0, 36);
}
void Cuboid::update()
{
	updateShading();
}
