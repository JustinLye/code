#ifndef __MODEL_H_INCLUDED__
#define __MODEL_H_INCLUDED__

// Models are complex objects composed of one or more shapes

#include"Shape.h"

class Model
{
public:
	Model();
	virtual void draw();
	virtual void buffer();
protected:
	std::vector<Shape> Shapes;

};

#endif
