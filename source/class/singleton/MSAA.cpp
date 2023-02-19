#include "GL/glew.h"
#include "GLFW/glfw3.h"

#include <iostream>

#include "class/singleton/Global.h"
#include "class/singleton/MSAA.h"
#include "enum/SHADING.h"
#include "static.hpp"

MSAA::MSAA() :
	frameBuffer(0),
	frameTexture(0),
	multiSamplingBuffer(0),
	multiSamplingTexture(0),
	renderBuffer(0)
{
	generate();
	bindTextureRender();
}
MSAA::~MSAA()
{
	expurgate();
}

void MSAA::bindFrameBuffer()const
{
	glBindFramebuffer(GL_FRAMEBUFFER, multiSamplingBuffer);
}
void MSAA::bindTextureRender()const
{
	glBindFramebuffer(GL_FRAMEBUFFER, multiSamplingBuffer);

	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, multiSamplingTexture);
	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, 4, GL_RGB, Global::singleton().canvasWidth, Global::singleton().canvasHeight, GL_TRUE);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D_MULTISAMPLE, multiSamplingTexture, 0);

	glBindRenderbuffer(GL_RENDERBUFFER, renderBuffer);
	glRenderbufferStorageMultisample(GL_RENDERBUFFER, 4, GL_DEPTH24_STENCIL8, Global::singleton().canvasWidth, Global::singleton().canvasHeight);
	glBindRenderbuffer(GL_RENDERBUFFER, 0);
	glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, renderBuffer);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) { std::cout << "MSAA::MSAA()  multiSamplingBuffer fail" << std::endl; }
	glBindFramebuffer(GL_FRAMEBUFFER, 0);

	glBindFramebuffer(GL_FRAMEBUFFER, frameBuffer);

	glBindTexture(GL_TEXTURE_2D, frameTexture);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Global::singleton().canvasWidth, Global::singleton().canvasHeight, 0, GL_RGB, GL_UNSIGNED_BYTE, NULL);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glBindTexture(GL_TEXTURE_2D, 0);
	glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0, GL_TEXTURE_2D, frameTexture, 0);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) { std::cout << "MSAA::MSAA()  frameTexture fail" << std::endl; }
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
}
void MSAA::draw()const
{
	glDisable(GL_DEPTH_TEST);


	glBindFramebuffer(GL_READ_FRAMEBUFFER, multiSamplingBuffer);
	glBindFramebuffer(GL_DRAW_FRAMEBUFFER, frameBuffer);
	glBlitFramebuffer(0, 0, Global::singleton().canvasWidth, Global::singleton().canvasHeight, 0, 0, Global::singleton().canvasWidth, Global::singleton().canvasHeight, GL_COLOR_BUFFER_BIT, GL_NEAREST);
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
void MSAA::expurgate()
{
	glDeleteBuffers(1, &frameBuffer);
	glDeleteBuffers(1, &multiSamplingBuffer);
	glDeleteBuffers(1, &renderBuffer);

	glDeleteTextures(1, &frameTexture);
	glDeleteTextures(1, &multiSamplingTexture);

	frameBuffer = 0;
	frameTexture = 0;
	multiSamplingBuffer = 0;
	multiSamplingTexture = 0;
	renderBuffer = 0;
}
void MSAA::generate()
{
	glGenFramebuffers(1, &frameBuffer);
	glGenFramebuffers(1, &multiSamplingBuffer);

	glGenRenderbuffers(1, &renderBuffer);

	glGenTextures(1, &frameTexture);
	glGenTextures(1, &multiSamplingTexture);
}
