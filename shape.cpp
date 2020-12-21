#include "shape.h"

shape::shape(geometry* geo, substance* sub, GLfloat x, GLfloat y, GLfloat z) : point(x, y, z)
{
	_geometry = geo;
	_substance = sub;
}

void shape::render(renderer* renderer)
{
	setup_transform(renderer);
	if (_substance) _substance->setup(renderer);
	if (_geometry) _geometry->setup(renderer);
	teardown(renderer);
}

void shape::setup_transform(renderer* renderer)
{
	renderer->local_world_begin();
	//glPushMatrix();
	point::setup(renderer);
	oriented::setup(renderer);
	extended::setup(renderer);
}

void shape::teardown(renderer* renderer)
{
	renderer->local_world_end();
	//glPopMatrix();
}
