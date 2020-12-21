#include "viewport.h"


viewport::viewport(GLsizei width, GLsizei height, GLdouble near_plane, GLdouble far_plane)
{
	set_size(width, height);
	set_clipping(near_plane, far_plane);
}

void viewport::setup(renderer* renderer)
{
	renderer->setup_viewport(this);
}

void viewport::set_size(GLsizei width, GLsizei height)
{
	_size.width = width;
	_size.height = height;
}

void viewport::set_clipping(GLdouble near_plane, GLdouble far_plane)
{
	_clipping.near_plane = near_plane;
	_clipping.far_plane = far_plane;
}

perspective::perspective(GLdouble fov, GLint width, GLint height, GLdouble near_plane, GLdouble far_plane) :
	viewport(width, height, near_plane, far_plane)
{
	set_fov(fov);
}

void perspective::setup(renderer* renderer)
{
	viewport::setup(renderer);
	renderer->setup_projection_begin();
	renderer->setup_projection(this);
}

void perspective::set_fov(GLdouble fov)
{
	_fov = fov;
}