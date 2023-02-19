#include <stb-image/stb_image.h>

#include "OpenSource/imgui/imgui.h"
#include "OpenSource/imgui/imgui_impl_glfw.h"
#include "OpenSource/imgui/imgui_impl_opengl3.h"

#include "initialization.h"

#include "class/Cuboid.h"
#include "class/Orthogon.h"
#include "class/Player.h"
#include "class/ShaderProgram.h"
#include "class/singleton/Frame.h"
#include "class/singleton/Global.h"
#include "class/singleton/MSAA.h"
#include "class/singleton/Temporary.h"
#include "function/print.h"
#include "function/universal.h"
#include "enum/SHADING.h"
#include "static.hpp"

void glewInitialization()
{
	if (glewInit() != GLEW_OK) { std::cout << "glewInit!=GLEW_OK" << std::endl; }
}
void glfwEnd()
{
	glfwDestroyWindow(Global::singleton().window);
	glfwTerminate();
}
void glfwInitialization()
{
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
	glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif
	Global::singleton().window = glfwCreateWindow(Global::singleton().canvasWidth, Global::singleton().canvasHeight, "GeometryLight", NULL, NULL);
	if (!Global::singleton().window) { std::cout << "!Global::singleton().window" << std::endl; }
	glfwMakeContextCurrent(Global::singleton().window);

	glViewport(0, 0, Global::singleton().canvasWidth, Global::singleton().canvasHeight);

	glEnable(GL_CULL_FACE);
	glCullFace(GL_BACK);

	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);

	glClearColor(0.125, 0.125, 0.125, 1);
}
void ImGuiEnd()
{
	ImGui_ImplGlfw_Shutdown();
	ImGui_ImplOpenGL3_Shutdown();
	ImGui::DestroyContext();
}
void ImGuiInitialization()
{
	IMGUI_CHECKVERSION();
	ImGui::CreateContext();
	ImGuiIO& imGuiIO = ImGui::GetIO();

	ImGui_ImplGlfw_InitForOpenGL(Global::singleton().window, true);
	ImGui_ImplOpenGL3_Init("#version 400");
	ImGui::StyleColorsDark();
}
void initialization()
{
	srand(time(NULL));

	constv();

	Global::singleton().deltaTime = constv().frameTime;
	Global::singleton().sensitivity = 0.25;
	Global::singleton().canvasHeight = 768;
	Global::singleton().canvasWidth = 1024;
	Global::singleton().frameIdle = 0;
	Global::singleton().frameOver = 0;
	Global::singleton().frameStart = 0;

	player();
}
void lateInitialization()
{
	Global::singleton().projection = glm::perspective(glm::radians(80.0f), static_cast<float>(Global::singleton().canvasWidth / Global::singleton().canvasHeight), constv().perspectiveNear, constv().perspectiveFar);
	
	Frame::singleton();
	MSAA::singleton();
	player().look();
	
	std::shared_ptr<Geometry> geometryShdPtr;

	Temporary::singleton().container = new Cuboid(glm::vec3(0.0f), glm::vec3(0.0f), glm::vec3(1.0f),
		SOLID, glm::vec4(1.0f, 0.0f, 0.0f, 1.0f),
		glm::vec3(200.0f, 200.0f, 200.0f),
		false, 128.0f, "resource/texture/container/container_diff.png", "resource/texture/container/container_spec.png");
	geometryShdPtr.reset(Temporary::singleton().container);
	Geometry::geometryList().push_back(geometryShdPtr);
	Temporary::singleton().container->formModel();
	Temporary::singleton().container->bindBufferArray();

	Temporary::singleton().bricks = new Orthogon(glm::vec3(0.0f, 0.0f, -600.0f), glm::vec3(0.0f), glm::vec3(1.0f),
		SOLID, glm::vec4(0.0f, 1.0f, 1.0f, 1.0f),
		glm::vec2(1000.0f, 1000.0f),
		false, 128.0f, "resource/texture/bricks/bricks_diff.jpg", "resource/texture/bricks/bricks_spec.jpg");
	geometryShdPtr.reset(Temporary::singleton().bricks);
	Geometry::geometryList().push_back(geometryShdPtr);
	Geometry::geometryList().back()->formModel();
	Geometry::geometryList().back()->bindBufferArray();

	Temporary::singleton().dirLight.direction = glm::vec3(1.0f, 210.0f, 165.0f);
	Temporary::singleton().dirLight.reflection.diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
	Temporary::singleton().dirLight.reflection.specular = glm::vec3(1.0f, 1.0f, 1.0f);

	Temporary::singleton().pointLightBox = new Cuboid(glm::vec3(-400.0f, 0.0f, 0.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(1.0f),
		SOLID, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec3(10.0f, 10.0f, 10.0f),
		false, -1);
	geometryShdPtr.reset(Temporary::singleton().pointLightBox);
	Geometry::geometryList().push_back(geometryShdPtr);
	Temporary::singleton().pointLightBox->formModel();
	Temporary::singleton().pointLightBox->bindBufferArray();
	Temporary::singleton().pointLight.compensation = 1000.0f;
	Temporary::singleton().pointLight.attenuation = glm::vec3(1.0f, 0.07f, 0.032f);
	Temporary::singleton().pointLight.position = Temporary::singleton().pointLightBox->getPosition();
	Temporary::singleton().pointLight.reflection.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	Temporary::singleton().pointLight.reflection.specular = glm::vec3(1.0f, 1.0f, 1.0f);

	Temporary::singleton().spotLightBox = new Cuboid(glm::vec3(0.0f, -300.0f, 0.0f), glm::vec3(0.0f, 90.0f, 90.0f), glm::vec3(1.0f),
		SOLID, glm::vec4(0.0f, 0.0f, 0.0f, 1.0f),
		glm::vec3(10.0f, 10.0f, 20.0f),
		false,-1);
	geometryShdPtr.reset(Temporary::singleton().spotLightBox);
	Geometry::geometryList().push_back(geometryShdPtr);
	Temporary::singleton().spotLightBox->formModel();
	Temporary::singleton().spotLightBox->bindBufferArray();
	Temporary::singleton().spotLight.compensation = 1000.0;
	Temporary::singleton().spotLight.cutoff = glm::vec2(30.0f, 45.0f);
	Temporary::singleton().spotLight.attenuation = glm::vec3(1.0f, 0.07f, 0.032f);
	Temporary::singleton().spotLight.position = Temporary::singleton().spotLightBox->getPosition();
	Temporary::singleton().spotLight.direction = Temporary::singleton().spotLightBox->getRotation();
	Temporary::singleton().spotLight.reflection.diffuse = glm::vec3(1.0f, 1.0f, 1.0f);
	Temporary::singleton().spotLight.reflection.specular = glm::vec3(1.0f, 1.0f, 1.0f);
}
void shaderProgramInitialization()
{
	ShaderProgram shaderPg("resource/shader/frame/frame");
	shaderProgramMap().insert(std::make_pair(FRAME, shaderPg));

	shaderPg.compile_link("resource/shader/line/line", false);
	shaderProgramMap().insert(std::make_pair(LINE, shaderPg));

	shaderPg.compile_link("resource/shader/geometry/geometry", false);
	shaderProgramMap().insert(std::make_pair(SOLID, shaderPg));

	shaderPg.compile_link("resource/shader/geometryLight/geometryLight", false);
	shaderProgramMap().insert(std::make_pair(RENDERED, shaderPg));
}
void stbInitialization()
{
	stbi_set_flip_vertically_on_load(true);
}
