#include "light.h"

light::light(material* mat): substance(mat)
{
	set_on(true);
}

light::~light()
{
	//disable();
}

void light::setup(GLuint index, renderer* renderer)
{
	substance::setup(index, renderer);
	renderer->setup_light(index, _is_on);
}

attenuated_light::attenuated_light(material* mat) : light(mat)
{}

void attenuated_light::setup(GLuint index, renderer* renderer)
{
	light::setup(index, renderer);
	renderer->setup_light(index, this);
	//glLightfv(GL_LIGHT0 + _number, GL_CONSTANT_ATTENUATION, &_attenuation[0]);
	//glLightfv(GL_LIGHT0 + _number, GL_LINEAR_ATTENUATION, &_attenuation[1]);
	//glLightfv(GL_LIGHT0 + _number, GL_QUADRATIC_ATTENUATION, &_attenuation[2]);
}

void attenuated_light::set_attenuation(GLfloat constant, GLfloat linear, GLfloat quadratic)
{
	_attenuation[0] = constant;
	_attenuation[1] = linear;
	_attenuation[2] = quadratic;
}


point_light::point_light(material* mat, GLfloat x, GLfloat y, GLfloat z): attenuated_light(mat), point(x,y,z)
{}

void point_light::setup(GLuint index, renderer* renderer)
{
	attenuated_light::setup(index, renderer);
	renderer->setup_light(index, this);
}


spotlight_light::spotlight_light(material* mat, GLfloat x, GLfloat y, GLfloat z,
	GLfloat dx, GLfloat dy, GLfloat dz, GLfloat cutoff, GLfloat exponent) :
	attenuated_light(mat), directional(x, y, z, dx, dy, dz)
{
	set_exponent(exponent);
	set_cutoff(cutoff);
}

void spotlight_light::setup(GLuint index, renderer* renderer)
{
	attenuated_light::setup(index, renderer);
	renderer->setup_light(index, this);
}

void spotlight_light::set_cutoff(GLfloat cutoff)
{
	_cutoff = cutoff;
}

void spotlight_light::set_exponent(GLfloat exponent)
{
	_exponent = exponent;
}

directional_light::directional_light(material* mat, GLfloat x, GLfloat y, GLfloat z, GLfloat targetx, GLfloat targety, GLfloat targetz) :
	light(mat), directional(x, y, z, targetx, targety, targetz)
{}

void directional_light::setup(GLuint index, renderer* renderer)
{
	light::setup(index, renderer);
	renderer->setup_light(index, this);
}
