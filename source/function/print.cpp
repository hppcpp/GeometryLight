#include <iostream>

#include "class/singleton/Global.h"
#include "function/print.h"
#include "static.hpp"

void constvPrint()
{
	printf("const\n");
	printf("frameTime==%d\n", constv().frameTime);
	printf("screenHeight==%d\n", constv().screenHeight);
	printf("screenHeightHalf==%d\n", constv().screenHeightHalf);
	printf("screenWidth==%d\n", constv().screenWidth);
	printf("screenWidthHalf==%d\n", constv().screenWidthHalf);
}
void frameTimePrint()
{
	printf("deltaTime==%lu\n", Global::singleton().deltaTime);
	printf("frameOver-frameStart==%lu\n", Global::singleton().frameOver - Global::singleton().frameStart);
}
void print()
{
	/**/
	printf("position==");
	vectorPrint(3,&player().getPosition()[0]);
	printf("spherical==");
	vectorPrint(3,&player().getRotation()[0]);
	printf("camera.spherical==");
	vectorPrint(3, &player().getCamera().getRotation()[0]);
	
}
void staticvPrint()
{
	printf("static\n");
	printf("sensitivity==%lf\n", Global::singleton().sensitivity);
	printf("windowRatio==%lf\n", Global::singleton().windowRatio);
	printf("canvasHeight==%d\n", Global::singleton().canvasHeight);
	printf("canvasWidth==%d\n", Global::singleton().canvasWidth);
	printf("deltaTime==%lu\n", Global::singleton().deltaTime);
	printf("frameStart==%lu\n", Global::singleton().frameStart);
	printf("frameOver==%lu\n", Global::singleton().frameOver);
}
