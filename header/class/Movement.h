#pragma once

#include "class/Transformation.h"

class Movement:public Transformation
{
public:
	Movement(const glm::vec3&, const glm::vec3&);

	virtual void getOrientation(float* const)const;
	void limit();
	void moveBack(double);
	void moveBack2D(double);
	void moveDown(double);
	void moveFront(double);
	void moveFront2D(double);
	void moveLeft(double);
	void moveLeft2D(double);
	void moveRight(double);
	void moveRight2D(double);
	void moveUp(double);
};
