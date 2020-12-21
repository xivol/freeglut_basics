#include "geometry.h"

geometry* sphere::Default = new sphere();

sphere::sphere(GLdouble radius, GLint slices, GLint stacks)
{
	_radius = radius; _slices = slices; _stacks = stacks;
}

geometry* torus::Default = new torus();

torus::torus(GLdouble innerRadius, GLdouble outerRadius, GLint sides, GLint rings)
{
	_innerRadius = innerRadius;
	_outerRadius = outerRadius;
	_sides = sides;
	_rings = rings;
}


geometry* cylinder::Default = new cylinder();

cylinder::cylinder(GLdouble base, GLdouble height, GLint slices, GLint stacks)
{
	_base = base;
	_height = height;
	_slices = slices;
	_stacks = stacks;
}


geometry* cone::Default = new cone();
cone::cone(GLdouble base, GLdouble height, GLint slices, GLint stacks)
{
	_base = base;
	_height = height;
	_slices = slices;
	_stacks = stacks;
}


geometry* tetrahedron::Default = new tetrahedron();

geometry* hexahedron::Default = new hexahedron();

geometry* octahedron::Default = new octahedron();

geometry* dodecahedron::Default = new dodecahedron();

geometry* icosahedron::Default = new icosahedron();

geometry* utah_teapot::Default = new utah_teapot();
