#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include "iostream"

#include "class/singleton/Frame.h"
#include "class/singleton/Global.h"
#include "enum/SHADING.h"
#include "static.hpp"

Frame::Frame() :
	frameBuffer(0),
	frameTexture(0),
	renderBuffer(0)
{
	generate();
	bindTextureRender();
}
Frame::~Frame()
{
	expurgate();
}

void Frame::bindFrameBuffer()const
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);
}
void Frame::bindTextureRender()const
{
	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	glBindTexture(GL_TEXTURE_2D, frameTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Global::singleton().canvasWidth, Global::singleton().canvasHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frameTexture, 0);

	glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
	glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, Global::singleton().canvasWidth, Global::singleton().canvasHeight);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) { std::cout << "Frame::Frame()  frameBuffer fail" << std::endl; }
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void Frame::draw()const
{
	glDisable(GL_DEPTH_TEST);


	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	glClear(GL_COLOR_BUFFER_BIT);

	const ShaderProgram& shaderPg = shaderProgramMap()[FRAME];
	shaderPg.getProgram().use();

	CAP::GLSL::activeBindTexture(0, GL_TEXTURE_2D, frameTexture);
	shaderPg.getProgram().setUniform1f("frameTexture", 0);

	glBindVertexArray(vertexArray);
	glDrawArrays(GL_TRIANGLES, 0, 6);


	glEnable(GL_DEPTH_TEST);
}
void Frame::expurgate()
{
	glDeleteBuffers(1, &frameBuffer);
	glDeleteBuffers(1, &renderBuffer);

	glDeleteTextures(1, &frameTexture);
	
	frameBuffer = 0;
	frameTexture = 0;
	renderBuffer = 0;
}
void Frame::generate()
{
	glGenFramebuffers(1, &frameBuffer);

	glGenRenderbuffers(1, &renderBuffer);

	glGenTextures(1, &frameTexture);
}
