#pragma once
#include "renderer.h"
#include "geometry.h"


class viewport: public render_param
{
protected:
	size _size = { 640,480 };

	struct clipping {
		GLdouble near_plane;
		GLdouble far_plane;
	} _clipping = { 1, 1000 };
public:
	viewport(GLsizei width, GLsizei height, GLdouble near_plane, GLdouble far_plane);
	virtual void setup(renderer* renderer);

	inline size& get_size() { return _size; }
	virtual void set_size(GLsizei width, GLsizei height);

	inline clipping get_clipping() { return _clipping; }
	virtual void set_clipping(GLdouble near_plane, GLdouble far_plane);
};

class perspective : public viewport
{
protected:
	GLdouble _fov = 90;
public:
	perspective(GLdouble fov, GLint width, GLint height, GLdouble near_plane, GLdouble far_plane);
	virtual void setup(renderer* renderer);

	inline GLdouble get_fov() { return _fov; }
	virtual void set_fov(GLdouble fov);
};

