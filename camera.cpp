#include "camera.h"

camera::camera(GLfloat x, GLfloat y, GLfloat z, GLfloat targetx, GLfloat targety, GLfloat targetz, GLfloat upx, GLfloat upy, GLfloat upz) : 
	directional(x, y, z, targetx, targety, targetz)
{
	set_up(upx, upy, upz);
}

void camera::setup(renderer* renderer)
{
	renderer->setup_view_begin();
	renderer->setup_view_look_at(this);
}

void camera::set_up(GLfloat x, GLfloat y, GLfloat z)
{
	_up.x = x; _up.y = y; _up.z = z;
}
