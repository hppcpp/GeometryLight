#pragma once

#include <windows.h>

class Constsv
{
	public:
		const int screenHeight,screenWidth,randomMax;
		
		Constsv():
			screenHeight(GetSystemMetrics(SM_CYSCREEN)),
			screenWidth(GetSystemMetrics(SM_CXSCREEN)),
			randomMax(pow(2,15))
		{}
};

class Constv:public Constsv
{
	public:
		const int frameTime,
			muzzleOffset,
			orthoX,orthoY,
			sceneOffset,sceneX,sceneY,sceneZ,
			screenHeightHalf,screenWidthHalf,
			sightAnchorX,sightAnchorY;
		const float perspectiveFar,perspectiveNear;
		const glm::vec3 origin;
		
		Constv():
			frameTime(100/6),
			muzzleOffset(500),
			orthoX(6144),
			orthoY(4096),
			sceneOffset(128),
			sceneX(65536),
			sceneY(65536),
			sceneZ(875),
			screenHeightHalf(screenHeight/2),
			screenWidthHalf(screenWidth/2),
			sightAnchorX(screenWidth/2),
			sightAnchorY(screenHeight/2+64),
			perspectiveFar(1048576),
			perspectiveNear(1),
			origin(glm::vec3(0,0,0))
		{}
};
