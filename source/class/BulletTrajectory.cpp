#include "class/BulletTrajectory.h"

#include "class/singleton/Global.h"
#include "function/universal.h"

const double BulletTrajectory::spell=1000;



BulletTrajectory::BulletTrajectory(double range, int shad, const glm::vec3& pos, const glm::vec3& dir, const glm::vec4& col,
	const glm::vec3& posi, const glm::vec3& rota, const glm::vec3& sca) :
	Ray(range, shad, pos, dir, col, posi, rota, sca),
	start(Global::singleton().frameStart)
{}

bool BulletTrajectory::getIsOver()const
{
	if (BulletTrajectory::spell <= Global::singleton().frameStart - start) { return true; }
	return false;
}
