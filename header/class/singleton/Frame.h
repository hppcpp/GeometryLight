#pragma once

#include "class/FrameVertex.h"

class Frame :public FrameVertex
{
protected:
	unsigned int frameBuffer,
		frameTexture,
		renderBuffer;

	Frame();
	Frame(const Frame&) {}
	Frame& operator=(const Frame&) {}
	~Frame();
public:
	static Frame& singleton()
	{
		static Frame value;
		return value;
	}



	void bindFrameBuffer()const;
	void bindTextureRender()const;
	void draw()const;
	void expurgate();
	void generate();

	unsigned int getFrameBuffer()const { return frameBuffer; }
};
