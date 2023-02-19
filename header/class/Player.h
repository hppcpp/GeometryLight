#pragma once

#include <string>

#include "class/Camera.h"
#include "class/Movement.h"
#include "class/singleton/Global.h"

class Player :public Movement
{
protected:
	bool automatic, trigger;
	//char state;
	double runSpeed, walkSpeed;
	int HP;
	Camera camera;
public:
	static const double range;
	static const int trajectoryShading;
	static const glm::vec4 trajectoryColor;

	explicit Player(const glm::vec3&, const glm::vec3&, double, double, int, const Camera&);

	void getOrientation(float* const)const;
	void getCameraPosition(float* const)const;
	inline void look()const { camera.look_tripod(*this); }
	inline void look_topDown()const { camera.look_topDown(*this); }
	inline void runBack() { moveBack(runSpeed); }
	inline void runBack2D() { moveBack2D(runSpeed); }
	inline void runDown() { moveDown(runSpeed); }
	inline void runFront() { moveFront(runSpeed); }
	inline void runFront2D() { moveFront2D(runSpeed); }
	inline void runLeft() { moveLeft(runSpeed); }
	inline void runLeft2D() { moveLeft2D(runSpeed); }
	inline void runRight() { moveRight(runSpeed); }
	inline void runRight2D() { moveRight2D(runSpeed); }
	inline void runUp() { moveUp(runSpeed); }
	void shoot();
	inline void turn() { camera.rotate_tripod(rotation); }
	inline void turn_topDown() { camera.rotate_topDown(rotation); }
	inline void walkBack() { moveBack(walkSpeed); }
	inline void walkBack2D() { moveBack2D(walkSpeed); }
	inline void walkDown() { moveDown(walkSpeed); }
	inline void walkFront() { moveFront(walkSpeed); }
	inline void walkFront2D() { moveFront2D(walkSpeed); }
	inline void walkLeft() { moveLeft(walkSpeed); }
	inline void walkLeft2D() { moveLeft2D(walkSpeed); }
	inline void walkRight() { moveRight(walkSpeed); }
	inline void walkRight2D() { moveRight2D(walkSpeed); }
	inline void walkUp() { moveUp(walkSpeed); }

	inline void runA() { position[0] -= runSpeed * Global::singleton().deltaTime; }
	inline void runD() { position[0] += runSpeed * Global::singleton().deltaTime; }
	inline void runS() { position[1] -= runSpeed * Global::singleton().deltaTime; }
	inline void runW() { position[1] += runSpeed * Global::singleton().deltaTime; }
	inline void walkA() { position[0] -= walkSpeed * Global::singleton().deltaTime; }
	inline void walkD() { position[0] += walkSpeed * Global::singleton().deltaTime; }
	inline void walkS() { position[1] -= walkSpeed * Global::singleton().deltaTime; }
	inline void walkW() { position[1] += walkSpeed * Global::singleton().deltaTime; }

	bool getAutomatic()const { return automatic; }
	bool getTrigger()const { return trigger; }
	//char getState()const{return state;}
	double getRunSpeed()const { return runSpeed; }
	double getWalkSpeed()const { return walkSpeed; }
	int getHP()const { return HP; }
	void setAutomatic(bool value) { automatic = value; }
	void setHP(int value) { HP = value; }
	void setRunSpeed(double value) { walkSpeed = value; }
	//void setState(char value){state=value;}
	void setTrigger(bool value) { trigger = value; }
	void setWalkSpeed(double value) { walkSpeed = value; }
	const Camera& getCamera()const { return camera; }
	Camera& setCamera() { return camera; }
};
