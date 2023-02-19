#include <algorithm>

#include "CAP/win.h"

#include "class/Geometry.h"
#include "class/singleton/Frame.h"
#include "class/singleton/Global.h"
#include "class/singleton/MSAA.h"
#include "class/singleton/Setting.h"
#include "class/singleton/Temporary.h"
#include "function/print.h"
#include "function/universal.h"
#include "functor.hpp"
#include "enum/SHADING.h"
#include "initialization.h"
#include "static.hpp"
#include "stem.h"

void displayFunc()
{
	//temporary
	float cameraPos[3], direction[3];
	const ShaderProgram& shaderPg = shaderProgramMap()[RENDERED];
	shaderPg.getProgram().use();

	player().getCameraPosition(cameraPos);
	shaderPg.getProgram().setUniform3f("cameraPos", cameraPos);

	shaderPg.getProgram().setUniform3f("ambient", &Temporary::singleton().ambient[0]);

	CAP::spherical_rectangular_normalized(&Temporary::singleton().dirLight.direction[0], direction);
	shaderPg.getProgram().setUniform3f("dirLight.direction", direction);
	shaderPg.getProgram().setUniform3f("dirLight.reflection.diffuse", &Temporary::singleton().dirLight.reflection.diffuse[0]);
	shaderPg.getProgram().setUniform3f("dirLight.reflection.specular", &Temporary::singleton().dirLight.reflection.specular[0]);

	shaderPg.getProgram().setUniform1f("pointLight.compensation", Temporary::singleton().pointLight.compensation);
	shaderPg.getProgram().setUniform3f("pointLight.position", &Temporary::singleton().pointLight.position[0]);
	shaderPg.getProgram().setUniform3f("pointLight.attenuation", &Temporary::singleton().pointLight.attenuation[0]);
	shaderPg.getProgram().setUniform3f("pointLight.reflection.diffuse", &Temporary::singleton().pointLight.reflection.diffuse[0]);
	shaderPg.getProgram().setUniform3f("pointLight.reflection.specular", &Temporary::singleton().pointLight.reflection.specular[0]);

	CAP::spherical_rectangular_normalized(&Temporary::singleton().spotLight.direction[0], direction);
	shaderPg.getProgram().setUniform1f("spotLight.compensation", Temporary::singleton().spotLight.compensation);
	shaderPg.getProgram().setUniform2f("spotLight.cutoff", cos(glm::radians(Temporary::singleton().spotLight.cutoff[0])), cos(glm::radians(Temporary::singleton().spotLight.cutoff[1])));
	shaderPg.getProgram().setUniform3f("spotLight.attenuation", &Temporary::singleton().spotLight.attenuation[0]);
	shaderPg.getProgram().setUniform3f("spotLight.direction", direction);
	shaderPg.getProgram().setUniform3f("spotLight.position", &Temporary::singleton().spotLight.position[0]);
	shaderPg.getProgram().setUniform3f("spotLight.reflection.diffuse", &Temporary::singleton().spotLight.reflection.diffuse[0]);
	shaderPg.getProgram().setUniform3f("spotLight.reflection.specular", &Temporary::singleton().spotLight.reflection.specular[0]);



	//display
	if (Setting::singleton().isMSAA) { MSAA::singleton().bindFrameBuffer(); }
	else{ Frame::singleton().bindFrameBuffer(); }
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	for_each(Geometry::geometryList().begin(), Geometry::geometryList().end(), DisplayGeometry());



	//draw
	if (Setting::singleton().isMSAA) { MSAA::singleton().draw(); }
	else { Frame::singleton().draw(); }

	

	displayImgui();
}
void framebufferSizeCallback(GLFWwindow* window, int width, int height)
{
	Global::singleton().canvasHeight = height;
	Global::singleton().canvasWidth = width;
	glViewport(0, 0, Global::singleton().canvasWidth, Global::singleton().canvasHeight);
	Global::singleton().projection = glm::perspective(glm::radians(80.0f), static_cast<float>(Global::singleton().canvasWidth / Global::singleton().canvasHeight), 1.0f, 1048576.0f);

	Frame::singleton().bindTextureRender();
	MSAA::singleton().bindTextureRender();
}

int main(int argc,char** argv)
{
	initialization();
	
	glfwInitialization();
	glfwSetFramebufferSizeCallback(Global::singleton().window, framebufferSizeCallback);

	glewInitialization();
	shaderProgramInitialization();

	stbInitialization();
	ImGuiInitialization();

	lateInitialization();

	//system("pause");
	while (!glfwWindowShouldClose(Global::singleton().window))
	{
		inputUpdate();
		update();
		lateUpdate();
		
		displayFunc();

		glfwSwapBuffers(Global::singleton().window);
		glfwPollEvents();
		
		Global::singleton().frameOver = GetTickCount64();
		Global::singleton().deltaTime = constv().frameTime * ((Global::singleton().frameOver - Global::singleton().frameStart) / constv().frameTime + 1);
		Global::singleton().frameIdle = constv().frameTime - ((Global::singleton().frameOver - Global::singleton().frameStart) % constv().frameTime);
		//std::cout << "frameIdle  " << frameIdle << std::endl;
		CAP_pause_spin(Global::singleton().frameIdle);
		Global::singleton().frameStart = GetTickCount64();
	}
	
	ImGuiEnd();

	glfwEnd();

	return 0;
}
