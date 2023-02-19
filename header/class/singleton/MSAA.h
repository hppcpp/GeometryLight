#pragma once

#include "class/FrameVertex.h"

class MSAA :public FrameVertex
{
private:
	unsigned int frameBuffer,
		frameTexture,
		multiSamplingBuffer,
		multiSamplingTexture,
		renderBuffer;

	MSAA();
	MSAA(const MSAA&) {}
	MSAA& operator=(const MSAA&) {}
	~MSAA();
public:
	static MSAA& singleton()
	{
		static MSAA value;
		return value;
	}



	void bindFrameBuffer()const;
	void bindTextureRender()const;
	void draw()const;
	void expurgate();
	void generate();

	unsigned int getFrameBuffer()const { return frameBuffer; }
	unsigned int getMultiSamplingBuffer()const { return multiSamplingBuffer; }
	unsigned int getRenderBuffer()const { return renderBuffer; }
};
