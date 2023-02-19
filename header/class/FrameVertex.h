#pragma once

class FrameVertex
{
protected:
	unsigned int vertexArray,vertexBuffer;
public:
	FrameVertex();
	~FrameVertex();

	void bindBufferArray()const;
	void expurgate();
	void generate();
};
