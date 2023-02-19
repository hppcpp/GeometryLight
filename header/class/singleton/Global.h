#pragma once

#include "GL/glew.h"
#include "GLFW/glfw3.h"
#include "windows.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "enum/GAME_MODE.h"

class Global
{
private:
	Global();
	Global(const Global&) {  }
	Global& operator=(const Global&) {  }
	~Global() {  }
public:
	static Global& singleton()
	{
		static Global value;
		return value;
	}

	bool mouse_debuging;
	double sensitivity, windowRatio;
	int canvasHeight, canvasWidth, windowPX, windowPY;
	DWORD deltaTime, frameIdle, frameOver, frameStart;
	GAME_MODE gameMode;
	GLFWwindow* window;
	glm::mat4 projection, view;
};
