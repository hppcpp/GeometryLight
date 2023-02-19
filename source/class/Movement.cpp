#include "CAP/GLT.hpp"

#include "class/Movement.h"
#include "function/universal.h"
#include "static.hpp"

Movement::Movement(const glm::vec3& posi, const glm::vec3& rota):
	Transformation(posi, rota)
{}

void Movement::getOrientation(float* const orientation)const
{
	memcpy(orientation, &rotation[0], sizeof(glm::vec3));
	orientation[0] = 1;
}
void Movement::limit()
{
	if (position.x < -constv().sceneX) { position.x = -constv().sceneX; }
	else if (constv().sceneX < position.x) { position.x = constv().sceneX; }
	if (position.y < -constv().sceneY) { position.y = -constv().sceneY; }
	else if (constv().sceneY < position.y) { position.y = constv().sceneY; }
}
void Movement::moveBack(double speed)
{
	float direction[3], orientation[3];
	getOrientation(orientation);
	CAP::spherical_rectangular(orientation, direction);
	CAP::vectorAddAssign(3, -speed * Global::singleton().deltaTime, &position[0], direction);
}
void Movement::moveBack2D(double speed)
{
	float direction[2];
	CAP::polar_rectangular(&rotation[0], direction);
	CAP::vectorAddAssign(2, -speed * Global::singleton().deltaTime, &position[0], direction);
}
void Movement::moveDown(double speed)
{
	float direction[3], orientation[3];
	getOrientation(orientation);
	spherical_rectangularUp(orientation, direction);
	CAP::vectorAddAssign(3, -speed * Global::singleton().deltaTime, &position[0], direction);
}
void Movement::moveFront(double speed)
{
	float direction[3], orientation[3];
	getOrientation(orientation);
	CAP::spherical_rectangular(orientation, direction);
	CAP::vectorAddAssign(3, speed * Global::singleton().deltaTime, &position[0], direction);
}
void Movement::moveFront2D(double speed)
{
	float direction[2];
	CAP::polar_rectangular(&rotation[0], direction);
	CAP::vectorAddAssign(2, speed * Global::singleton().deltaTime, &position[0], direction);
}
void Movement::moveLeft(double speed)
{
	float direction[3], orientation[3];
	getOrientation(orientation);
	spherical_rectangularRight(orientation, direction);
	CAP::vectorAddAssign(3, -speed * Global::singleton().deltaTime, &position[0], direction);
}
void Movement::moveLeft2D(double speed)
{
	float direction[2];
	polar_rectangularRight(&rotation[0], direction);
	CAP::vectorAddAssign(2, -speed * Global::singleton().deltaTime, &position[0], direction);
}
void Movement::moveRight(double speed)
{
	float direction[3], orientation[3];
	getOrientation(orientation);
	spherical_rectangularRight(orientation, direction);
	CAP::vectorAddAssign(3, speed * Global::singleton().deltaTime, &position[0], direction);
}
void Movement::moveRight2D(double speed)
{
	float direction[2];
	polar_rectangularRight(&rotation[0], direction);
	CAP::vectorAddAssign(2, speed * Global::singleton().deltaTime, &position[0], direction);
}
void Movement::moveUp(double speed)
{
	float direction[3], orientation[3];
	getOrientation(orientation);
	spherical_rectangularUp(orientation, direction);
	CAP::vectorAddAssign(3, speed * Global::singleton().deltaTime, &position[0], direction);
}
