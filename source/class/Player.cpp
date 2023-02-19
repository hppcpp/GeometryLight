#include "CAP/GLT.hpp"

#include "class/Player.h"
#include "class/BulletTrajectory.h"
#include "function/universal.h"
#include "enum/SHADING.h"
#include "static.hpp"

const double Player::range = 65536;
const int Player::trajectoryShading = LINE;
const glm::vec4 Player::trajectoryColor = glm::vec4(0.75f, 0.75f, 0.75f, 1.0f);



Player::Player(const glm::vec3& posi, const glm::vec3& rota, double ruSpe, double waSpe, int hp, const Camera& cam) :
	Movement(posi, rota),
	automatic(false),
	trigger(false),
	//state(sta),
	runSpeed(ruSpe),
	walkSpeed(waSpe),
	HP(hp),
	camera(cam)
{}

void Player::getOrientation(float* const orientation)const
{
	orientation[0] = 1;
	orientation[1] = rotation[1];
	orientation[2] = rotation[2] + camera.getRotation()[2];
}
void Player::getCameraPosition(float* const cameraPos)const
{
	memcpy(cameraPos, &position[0], sizeof(glm::vec3));
	CAP::vectorAddAssign(3, 1, cameraPos, &camera.getPosition()[0]);
}
void Player::shoot()
{
	trigger = true;

	double rayLength = Player::range;
	glm::vec3 rayPosition, rayRotation;
	getCameraPosition(&rayPosition[0]);
	getOrientation(&rayRotation[0]);
	Geometry::geometryList().push_back(std::make_shared<BulletTrajectory>(Player::range, Player::trajectoryShading, rayPosition, rayRotation, trajectoryColor));
	Geometry::geometryList().back()->formModel();
	Geometry::geometryList().back()->bindBufferArray();
}
