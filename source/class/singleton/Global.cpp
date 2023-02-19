#pragma once

#include "class/Ray.h"
#include "class/singleton/Global.h"

Global::Global() :
	mouse_debuging(false),
	sensitivity(0),
	windowRatio(0),
	canvasHeight(0),
	canvasWidth(0),
	windowPX(0),
	windowPY(0),
	deltaTime(0),
	frameIdle(0),
	frameOver(0),
	frameStart(0),
	gameMode(GAME_DEBUG),
	window(0),
	projection(glm::mat4(1.0f)),
	view(glm::mat4(1.0f))
{}
