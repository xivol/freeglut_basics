#pragma once
#include "renderer.h"
#include "world_transform.h" 

class camera : public directional, public render_param
{
protected:
	vec3D _up = { 0,1,0,1 };
public:
	camera(GLfloat x, GLfloat y, GLfloat z, GLfloat dx, GLfloat dy, GLfloat dz, GLfloat upx, GLfloat upy, GLfloat upz);
	virtual void setup(renderer* renderer);

	inline vec3D get_up() const { return _up; }
	virtual void set_up(GLfloat x, GLfloat y, GLfloat z);
};

