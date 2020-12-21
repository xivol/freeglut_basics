#include "material.h"
#include <iostream>
color color::BLACK = color(0, 0, 0, 0);
color color::WHITE = color(1, 1, 1, 0);

color color::RED = color(1, 0, 0, 0);
color color::GREEN = color(0, 1, 0, 0);
color color::BLUE = color(0, 0, 1, 0);

color color::YELLOW = color(1, 1, 0, 0);
color color::CYAN = color(0, 1, 1, 0);
color color::MAGENTA = color(1, 0, 1, 0);

color::color(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha)
{
	_rgba.r = red; _rgba.g = green; _rgba.b = blue; _rgba.a = alpha;
}

void color::setup(renderer* renderer)
{
	renderer->setup_vertex_color(this);
}

void color::setup(GLuint index, renderer* renderer)
{
	renderer->setup_light(index, this);
}

color color::operator*(double value)
{
	return color(_rgba.r*value, _rgba.g *value, _rgba.b*value, _rgba.a*value);
}

color::operator GLfloat*()
{
	return _rgba.values;
}

phong::phong(const color& color)
{
	set_ambient(color);
	set_diffuse(color);
}

void phong::setup(renderer* renderer)
{
	renderer->setup_material(this);
	//glMaterialfv(GL_FRONT, GL_AMBIENT, _ambient);
	//glMaterialfv(GL_FRONT, GL_DIFFUSE, _diffuse);
	//glMaterialfv(GL_FRONT, GL_SPECULAR, _specular);
	//glMaterialfv(GL_FRONT, GL_EMISSION, _emission);
	//glMaterialfv(GL_FRONT, GL_SHININESS, &_shininess);
}

void phong::setup(GLuint index, renderer* renderer)
{
	renderer->setup_light(index, this);
}

//color phong::ambient()
//{
//	return _ambient;
//}

void phong::set_ambient(const color& color)
{
	_ambient = color;
}

void phong::set_ambient(GLfloat red, GLfloat green, GLfloat blue)
{
	set_ambient(color(red, green, blue));
}

//color phong::diffuse()
//{
//	return _diffuse;
//}

void phong::set_diffuse(const color& color)
{
	_diffuse = color;
}

void phong::set_diffuse(GLfloat red, GLfloat green, GLfloat blue)
{
	set_diffuse(color(red, green, blue));
}

//color phong::specular()
//{
//	return _specular;
//}

void phong::set_specular(const color& color)
{
	_specular = color;
}

void phong::set_specular(GLfloat red, GLfloat green, GLfloat blue)
{
	set_specular(color(red, green, blue));
}

//color phong::emission()
//{
//	return _emission;
//}

void phong::set_emission(const color& color)
{
	_emission = color;
}

void phong::set_emission(GLfloat red, GLfloat green, GLfloat blue)
{
	set_emission(color(red, green, blue));
}

//GLfloat phong::shininess()
//{
//	return _shininess;
//}

void phong::set_shininess(GLfloat shininess)
{
	_shininess = shininess;
}
