#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <list>
#include <memory>
#include <string>

#include "class/ShaderProgram.h"
#include "class/Transformation.h"
#include "struct/Material.h"

class Geometry : public Transformation
{
protected:
	bool isOver;
	int shading;
	unsigned int vertexArray, vertexBuffer;
	glm::vec4 color;
public:
	static std::list<std::shared_ptr<Geometry> >& geometryList()
	{
		static std::list<std::shared_ptr<Geometry> > value;
		return value;
	}



	Geometry();
	explicit Geometry(const glm::vec3&, const glm::vec3&, const glm::vec3&,
		int, const glm::vec4&);
	virtual ~Geometry();

	virtual void bindBufferArray()const {  }
	virtual void draw()const {  }
	void expurgate();
	void generate();
	virtual void update() {  }
	void updateShading();
	ShaderProgram& initShader()const;

	virtual bool getIsOver()const { return isOver; }
	int getShading()const { return shading; }
	void setIsOver(bool value) { isOver = value; }
	void setShading(int value) { shading = value; }
	const glm::vec4& getColor()const { return color; }
	glm::vec4& setColor() { return color; }
};
