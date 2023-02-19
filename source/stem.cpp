#include <limits.h>

#include <algorithm>

#include "OpenSource/imgui/imgui.h"
#include "OpenSource/imgui/imgui_impl_glfw.h"
#include "OpenSource/imgui/imgui_impl_opengl3.h"

#include "class/Player.h"
#include "class/ShaderProgram.h"
#include "class/singleton/Global.h"
#include "class/singleton/ImGuiSetting.h"
#include "class/singleton/Setting.h"
#include "class/singleton/Temporary.h"
#include "function/print.h"
#include "function/universal.h"
#include "functor.hpp"
#include "enum/SHADING.h"
#include "static.hpp"
#include "stem.h"

void displayImgui()
{
	ImGui_ImplGlfw_NewFrame();
	ImGui_ImplOpenGL3_NewFrame();
	ImGui::NewFrame();

	ImGui::Begin("GeometryLight");
	if (ImGui::CollapsingHeader("ImGuiSetting")) { ImGui::DragFloat("dragSpeed", &ImGuiSetting::singleton().dragSpeed, 0.1f, 0.0f, ULONG_MAX); }
	if (ImGui::CollapsingHeader("Setting"))
	{
		ImGui::Checkbox("isMSAA", &Setting::singleton().isMSAA);
		if (ImGui::CollapsingHeader("SHADING"))
		{
			ImGui::RadioButton("SOLID", &Setting::singleton().shading, SOLID);
			ImGui::RadioButton("RENDERED", &Setting::singleton().shading, RENDERED);
		}
	}

	if (ImGui::CollapsingHeader("bricks"))
	{
		ImGui::DragFloat3("scale", &Temporary::singleton().bricks->setScale()[0], ImGuiSetting::singleton().dragSpeed);
		ImGui::DragFloat3("rotation", &Temporary::singleton().bricks->setRotation()[0], ImGuiSetting::singleton().dragSpeed, 0.0f, 360.0f);
		ImGui::DragFloat3("position", &Temporary::singleton().bricks->setPosition()[0], ImGuiSetting::singleton().dragSpeed);
		ImGui::DragFloat2("pCube", &Temporary::singleton().bricks->setPOrthogon()[0], ImGuiSetting::singleton().dragSpeed, 0.0f, ULONG_MAX);
		ImGui::ColorEdit4("color", &Temporary::singleton().bricks->setColor()[0]);
		ImGui::DragFloat("shininess", &Temporary::singleton().bricks->setMaterial().shininess, ImGuiSetting::singleton().dragSpeed, 0.0f, ULONG_MAX);
		if (ImGui::Button("isMaterial"))
		{
			if (Temporary::singleton().bricks->getIsMaterial()) { Temporary::singleton().bricks->setIsMaterial(false); }
			else { Temporary::singleton().bricks->setIsMaterial(true); }
		}
	}

	if (ImGui::CollapsingHeader("container"))
	{
		ImGui::DragFloat3("scale", &Temporary::singleton().container->setScale()[0], ImGuiSetting::singleton().dragSpeed);
		ImGui::DragFloat3("rotation", &Temporary::singleton().container->setRotation()[0], ImGuiSetting::singleton().dragSpeed, 0.0f, 360.0f);
		ImGui::DragFloat3("position", &Temporary::singleton().container->setPosition()[0], ImGuiSetting::singleton().dragSpeed);
		ImGui::DragFloat3("pCube", &Temporary::singleton().container->setPCuboid()[0], ImGuiSetting::singleton().dragSpeed, 0.0f, ULONG_MAX);
		ImGui::ColorEdit4("color", &Temporary::singleton().container->setColor()[0]);
		ImGui::DragFloat("shininess", &Temporary::singleton().container->setMaterial().shininess, ImGuiSetting::singleton().dragSpeed, 0.0f, ULONG_MAX);
		if (ImGui::Button("isMaterial"))
		{
			if (Temporary::singleton().container->getIsMaterial()) { Temporary::singleton().container->setIsMaterial(false); }
			else { Temporary::singleton().container->setIsMaterial(true); }
		}
	}
	
	if (ImGui::CollapsingHeader("ambient light")) { ImGui::ColorEdit3("ambient", &Temporary::singleton().ambient[0]); }

	if (ImGui::CollapsingHeader("direction light"))
	{
		ImGui::DragFloat2("direction", &Temporary::singleton().dirLight.direction[1], ImGuiSetting::singleton().dragSpeed, 0.0f, 360.0f);
		ImGui::ColorEdit3("diffuse", &Temporary::singleton().dirLight.reflection.diffuse[0]);
		ImGui::ColorEdit3("specular", &Temporary::singleton().dirLight.reflection.specular[0]);
	}

	if (ImGui::CollapsingHeader("point light"))
	{
		ImGui::DragFloat("compensation", &Temporary::singleton().pointLight.compensation, ImGuiSetting::singleton().dragSpeed, 0.0f, ULONG_MAX);
		ImGui::DragFloat3("attenuation", &Temporary::singleton().pointLight.attenuation[0], ImGuiSetting::singleton().dragSpeed, 0.001f, ULONG_MAX);
		ImGui::DragFloat3("position", &Temporary::singleton().pointLight.position[0], ImGuiSetting::singleton().dragSpeed);
		ImGui::ColorEdit3("diffuse", &Temporary::singleton().pointLight.reflection.diffuse[0]);
		ImGui::ColorEdit3("specular", &Temporary::singleton().pointLight.reflection.specular[0]);
	}

	if (ImGui::CollapsingHeader("spot light"))
	{
		ImGui::DragFloat("compensation", &Temporary::singleton().spotLight.compensation, ImGuiSetting::singleton().dragSpeed, 0.0f, ULONG_MAX);
		ImGui::DragFloat2("cutoff", &Temporary::singleton().spotLight.cutoff[0], ImGuiSetting::singleton().dragSpeed, 0.0f, 180.0f);
		ImGui::DragFloat3("attenuation", &Temporary::singleton().spotLight.attenuation[0], ImGuiSetting::singleton().dragSpeed, 0.001f, ULONG_MAX);
		ImGui::DragFloat2("direction", &Temporary::singleton().spotLight.direction[1], ImGuiSetting::singleton().dragSpeed, 0.0f, 360.0f);
		ImGui::DragFloat3("position", &Temporary::singleton().spotLight.position[0], ImGuiSetting::singleton().dragSpeed);
		ImGui::ColorEdit3("diffuse", &Temporary::singleton().spotLight.reflection.diffuse[0]);
		ImGui::ColorEdit3("specular", &Temporary::singleton().spotLight.reflection.specular[0]);
	}
	ImGui::End();

	Temporary::singleton().bricks->formModel();
	Temporary::singleton().bricks->bindBufferArray();
	Temporary::singleton().container->formModel();
	Temporary::singleton().container->bindBufferArray();

	Temporary::singleton().pointLightBox->setPosition() = Temporary::singleton().pointLight.position;
	Temporary::singleton().pointLightBox->setColor() = glm::vec4(Temporary::singleton().pointLight.reflection.diffuse, 1.0f);
	Temporary::singleton().pointLightBox->formModel();

	Temporary::singleton().spotLightBox->setPosition() = Temporary::singleton().spotLight.position;
	Temporary::singleton().spotLightBox->setRotation() = Temporary::singleton().spotLight.direction;
	Temporary::singleton().spotLightBox->setColor() = glm::vec4(Temporary::singleton().spotLight.reflection.diffuse, 1.0f);
	Temporary::singleton().spotLightBox->formModel();

	ImGui::Render();
	ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}
void inputUpdate()
{
	keyboard();

	if (Global::singleton().gameMode == GAME_DEBUG)
	{
		keyboard_FPS();
		mouse_debug();
		mouse();
	}
	else
	{
		if (Global::singleton().gameMode == FPS)
		{
			player().turn();
			keyboard_FPS();
			mouse();
		}
		else if (Global::singleton().gameMode == TOP_DOWN)
		{
			player().turn_topDown();
			keyboard_topDown();
			mouse();
		}
	}
}
void keyboard()
{
	if (glfwGetKey(Global::singleton().window, GLFW_KEY_L) == GLFW_PRESS) { print(); }
	if (glfwGetKey(Global::singleton().window, GLFW_KEY_O) == GLFW_PRESS) { exit(0); }
	if (glfwGetKey(Global::singleton().window, GLFW_KEY_P) == GLFW_PRESS) { system("pause"); }
}
void keyboard_FPS()
{
	if (glfwGetKey(Global::singleton().window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		if (glfwGetKey(Global::singleton().window, GLFW_KEY_A) == GLFW_PRESS) { player().runLeft(); }
		if (glfwGetKey(Global::singleton().window, GLFW_KEY_D) == GLFW_PRESS) { player().runRight(); }
		if (glfwGetKey(Global::singleton().window, GLFW_KEY_S) == GLFW_PRESS) { player().runBack(); }
		if (glfwGetKey(Global::singleton().window, GLFW_KEY_W) == GLFW_PRESS) { player().runFront(); }
		if (glfwGetKey(Global::singleton().window, GLFW_KEY_Q) == GLFW_PRESS) { player().runDown(); }
		if (glfwGetKey(Global::singleton().window, GLFW_KEY_E) == GLFW_PRESS) { player().runUp(); }
	}
	else
	{
		if (glfwGetKey(Global::singleton().window, GLFW_KEY_A) == GLFW_PRESS) { player().walkLeft(); }
		if (glfwGetKey(Global::singleton().window, GLFW_KEY_D) == GLFW_PRESS) { player().walkRight(); }
		if (glfwGetKey(Global::singleton().window, GLFW_KEY_S) == GLFW_PRESS) { player().walkBack(); }
		if (glfwGetKey(Global::singleton().window, GLFW_KEY_W) == GLFW_PRESS) { player().walkFront(); }
		if (glfwGetKey(Global::singleton().window, GLFW_KEY_Q) == GLFW_PRESS) { player().walkDown(); }
		if (glfwGetKey(Global::singleton().window, GLFW_KEY_E) == GLFW_PRESS) { player().walkUp(); }
	}
}
void keyboard_topDown()
{
	if (glfwGetKey(Global::singleton().window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS)
	{
		if (glfwGetKey(Global::singleton().window, GLFW_KEY_A) == GLFW_PRESS) { player().runA(); }
		if (glfwGetKey(Global::singleton().window, GLFW_KEY_D) == GLFW_PRESS) { player().runD(); }
		if (glfwGetKey(Global::singleton().window, GLFW_KEY_S) == GLFW_PRESS) { player().runS(); }
		if (glfwGetKey(Global::singleton().window, GLFW_KEY_W) == GLFW_PRESS) { player().runW(); }
	}
	else
	{
		if (glfwGetKey(Global::singleton().window, GLFW_KEY_A) == GLFW_PRESS) { player().walkA(); }
		if (glfwGetKey(Global::singleton().window, GLFW_KEY_D) == GLFW_PRESS) { player().walkD(); }
		if (glfwGetKey(Global::singleton().window, GLFW_KEY_S) == GLFW_PRESS) { player().walkS(); }
		if (glfwGetKey(Global::singleton().window, GLFW_KEY_W) == GLFW_PRESS) { player().walkW(); }
	}
}
void lateUpdate()
{
	if (Global::singleton().gameMode == GAME_DEBUG) { player().look(); }
	else
	{
		if (Global::singleton().gameMode == FPS) { player().look(); }
		else if (Global::singleton().gameMode == TOP_DOWN) { player().look_topDown(); }
	}
}
void mouse()
{
	//glfwSetInputMode(Global::singleton().window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
	if (glfwGetMouseButton(Global::singleton().window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_TRUE)
	{
		if (!player().getTrigger() || player().getAutomatic()) { player().shoot(); }
	}
	else { player().setTrigger(false); }
}
void mouse_debug()
{
	if (glfwGetMouseButton(Global::singleton().window, GLFW_MOUSE_BUTTON_RIGHT) == GLFW_TRUE)
	{
		if (!Global::singleton().mouse_debuging)
		{
			SetCursorPos(constv().sightAnchorX, constv().sightAnchorY);
			Global::singleton().mouse_debuging = true;
		}
		player().turn();
	}
	else { Global::singleton().mouse_debuging = false; }
}
void update()
{
	Geometry::geometryList().remove_if(geometryIsOver);

	for_each(Geometry::geometryList().begin(), Geometry::geometryList().end(), UpdateGeometry());
}
