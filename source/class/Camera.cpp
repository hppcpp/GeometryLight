#include <windows.h>

#include "CAP/GLT.hpp"

#include "class/Camera.h"
#include "class/singleton/Global.h"
#include "function/universal.h"
#include "static.hpp"

Camera::Camera(const glm::vec3& posi, const glm::vec3& rota) :
	Transformation(posi, rota)
{}

void Camera::look()const
{
	glm::vec3 rectangular, up;
	CAP::spherical_rectangular(&rotation[0], &rectangular[0]);
	spherical_rectangularUp(&rotation[0], &up[0]);
	glFrustum(-10, 10, -10, 10, 10, 1048576);
	Global::singleton().view = lookAt(position, position + rectangular, up);
}
void Camera::look_topDown(const Transformation& tripod)const
{
	Global::singleton().projection = glm::ortho(tripod.getPosition()[0] - constv().orthoX, tripod.getPosition()[0] + constv().orthoX,
		tripod.getPosition()[1] - constv().orthoY, tripod.getPosition()[1] + constv().orthoY,
		-16384.0f, 16384.0f);
	Global::singleton().view = glm::lookAt(glm::vec3(0.0f, 0.0f, 1.0f), glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f));
}
void Camera::look_tripod(const Transformation& tripod)const
{
	glm::vec3 orientation, rectangular, up;
	orientation[0] = 1;
	orientation[1] = tripod.getRotation()[1];
	orientation[2] = tripod.getRotation()[2] + rotation[2];
	CAP::spherical_rectangular(&orientation[0], &rectangular[0]);
	spherical_rectangularUp(&orientation[0], &up[0]);
	Global::singleton().view = lookAt(tripod.getPosition() + position, tripod.getPosition() + position + rectangular, up);
}
void Camera::rotate()
{
	POINT pMouse;
	GetCursorPos(&pMouse);
	SetCursorPos(constv().sightAnchorX, constv().sightAnchorY);

	double phi = rotation[2] + (pMouse.y - constv().sightAnchorY) * Global::singleton().sensitivity,
		theta = rotation[1] + (constv().sightAnchorX - pMouse.x) * Global::singleton().sensitivity;
	theta = static_cast<int>(theta + CAP::PERIGON) % CAP::PERIGON;
	if (phi < 0) { phi = 0; }
	else if (CAP::SA < phi) { phi = CAP::SA; }
	rotation = glm::vec3(0, theta, phi);
}
void Camera::rotate_topDown(glm::vec3& tripodRotation)
{
	POINT pMouse;
	GetCursorPos(&pMouse);

	double polar[2], rectangular[2];
	rectangular[0] = pMouse.x - constv().screenWidthHalf;
	rectangular[1] = constv().screenHeightHalf - pMouse.y;
	CAP::rectangular_polar(rectangular, polar);
	tripodRotation[1] = polar[1];
}
void Camera::rotate_tripod(glm::vec3& tripodRotation)
{
	POINT pMouse;
	GetCursorPos(&pMouse);
	SetCursorPos(constv().sightAnchorX, constv().sightAnchorY);

	double phi = rotation[2] + (pMouse.y - constv().sightAnchorY) * Global::singleton().sensitivity;
	double theta = tripodRotation[1] + (constv().sightAnchorX - pMouse.x) * Global::singleton().sensitivity;
	theta = static_cast<int>(theta + CAP::PERIGON) % CAP::PERIGON;
	/**/
	if (phi < 0) { phi = 0; }
	else if (CAP::SA < phi) { phi = CAP::SA; }
	rotation[2] = phi;
	
	tripodRotation[1] = theta;
}