#include "world_transform.h"

point::point(GLfloat x, GLfloat y, GLfloat z)
{
	set_position(x, y, z);
}

void point::set_position(GLfloat x, GLfloat y, GLfloat z)
{
	_position.x = x; _position.y = y; _position.z = z;
}

void point::set_position(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	set_position(x, y, z); _position.w = w;
}

void point::translate_by(GLfloat x, GLfloat y, GLfloat z)
{
	set_position(_position.x + x, _position.y + y, _position.z + z);
}

 void point::setup(renderer* renderer)
{
	glTranslatef(_position.x, _position.y, _position.z);
}

 void oriented::set_rotation(GLfloat x, GLfloat y, GLfloat z)
{
	_rotation.x = x; _rotation.y = y; _rotation.z = z;
}

void oriented::set_rotation(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	set_rotation(x, y, z); _rotation.w = w;
}

void oriented::rotate_by(GLfloat x, GLfloat y, GLfloat z)
{
	set_rotation(_rotation.x + x, _rotation.y + y, _rotation.z + z);
}

void oriented::setup(renderer* renderer)
{
	glRotatef(_rotation.x, 1, 0, 0);
	glRotatef(_rotation.y, 0, 1, 0);
	glRotatef(_rotation.z, 0, 0, 1);
}

void extended::set_scale(GLfloat x, GLfloat y, GLfloat z)
{
	_scale.x = x; _scale.y = y; _scale.z = z;
}

void extended::set_scale(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	set_scale(x, y, z); _scale.w = w;
}

void extended::scale_by(GLfloat x, GLfloat y, GLfloat z)
{
	set_scale(_scale.x + x, _scale.y + y, _scale.z + z);
}

void extended::setup(renderer* renderer)
{
	glScalef(_scale.x, _scale.y, _scale.z);
}


directional::directional(GLfloat x, GLfloat y, GLfloat z, GLfloat targetx, GLfloat targety, GLfloat targetz) : point(x, y, z)
{
	set_target(targetx, targety, targetz);
}

//void directional::setup_world() const
//{
//	point::setup_world();
//	oriented::setup_world();
//}

void directional::set_position(GLfloat x, GLfloat y, GLfloat z)
{
	point::set_position(x, y, z);
	reset_direction();
}

void directional::set_target(GLfloat x, GLfloat y, GLfloat z, GLfloat w)
{
	_target.x = x; _target.y = y; _target.z = z; _target.w = w;
	reset_direction();
}

void directional::translate_target_by(GLfloat x, GLfloat y, GLfloat z)
{
	_target.x += x; _target.y += y; _target.z += z;
	reset_direction();
}

void directional::reset_direction()
{
	_direction = get_direction();
	oriented::set_rotation(0, 0, 0);
}

vec3D directional::get_direction()
{
	return _target - _position;
}

void directional::set_rotation(GLfloat x, GLfloat y, GLfloat z)
{
	oriented::set_rotation(x, y, z);

	glPushMatrix();
	glTranslatef(_position.x, _position.y, _position.z);
	glRotatef(_rotation.x, 1, 0, 0);
	glRotatef(_rotation.y, 0, 1, 0);
	glRotatef(_rotation.z, 0, 0, 1);
	matrix m;
	glGetFloatv(GL_MODELVIEW_MATRIX, m);
	glPopMatrix();
	
	vec3D dir = m * _direction;
	_target = _position + dir;
}
