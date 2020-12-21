#pragma once
#include "renderer.h"
#include "material.h"
#include "geometry.h"
#include "world_transform.h"

class shape: public point, public oriented, public extended, public renderable
{
protected:
	geometry* _geometry;
	substance* _substance;
	virtual void setup_transform(renderer* renderer);
	virtual void teardown(renderer* renderer);
public:
	shape(geometry* geo, substance* sub, GLfloat x, GLfloat y, GLfloat z);

	substance* get_substance();
	geometry* get_geometry();

	virtual void render(renderer* renderer);
};
