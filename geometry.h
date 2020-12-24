#pragma once
#ifndef geometry_h
#define geometry_h
#include "math.h"
#include "renderer.h"
#include <vector>


struct size {
	GLsizei width;
	GLsizei height;
};


template <typename TData>
class triangle_data 
{
protected:
	std::vector<GLint> _indices;
	std::vector<TData> _data;

	inline void set_indices(std::vector<GLint>& indices) { _indices = indices; }
	inline void set_data(std::vector<TData>& data) { _data = data; }
public:
	triangle_data() : _data(), _indices() {}
	triangle_data(std::vector<TData>& data, std::vector<GLint>& indices) : _data(data), _indices(indices) {}
	
	inline std::vector<TData>& get_data() { return _data; }
	inline TData get_data(int index) { return _data[index]; }
	inline void set_data(int index, const TData& value) { _data[index] = value; }
	inline void add_data(const TData& value) { _data.push_back(value); }

	inline std::vector<GLint>& get_indices() { return _indices; }
	inline void add_triangle(GLint a, GLint b, GLint c) 
	{ 
		_indices.push_back(a); _indices.push_back(b); _indices.push_back(c); 
	}
	
	inline TData operator[](int index) { return _data[_indices[index]]; }
	inline size_t size() { return _indices.size(); }
};

template <typename TData>
class nested_data : public triangle_data<TData>, 
	public decorator<render_index_param>
{
protected: 
	virtual void setup_data(TData* data, renderer* render) = 0;
public:
	inline nested_data(render_index_param* base_data) : decorator(base_data)
	{}
	inline virtual void setup(GLuint index, renderer* render)
	{
		if(_base) _base->setup(index, render);
        TData t =this->operator[](index);
		setup_data(&t, render);
	}
};


class geometry : public render_param {};

class sphere : public geometry 
{
protected:
	GLdouble _radius;
	GLint _slices;
	GLint _stacks;
public:
	sphere(GLdouble radius = 1, GLint slices = 30, GLint stacks = 30);
	inline virtual void setup(renderer* renderer) { renderer->render(this); }

	inline GLdouble get_radius() { return _radius; }
	inline GLint get_slices() { return _slices; }
	inline GLint get_stacks() { return _stacks; }

	static geometry* Default;
};

class torus : public geometry 
{
protected:
	GLdouble _innerRadius; 
	GLdouble _outerRadius;
	GLint _sides;
	GLint _rings;
public:
	torus(GLdouble _innerRadius = 0.3, GLdouble _outerRadius = 0.7, GLint _sides = 30, GLint _rings = 30);
	inline virtual void setup(renderer* renderer) { renderer->render(this); }

	inline GLdouble get_inner_radius() { return _innerRadius; }
	inline GLdouble get_outer_radius() { return _outerRadius; }
	inline GLint get_sides() { return _sides; }
	inline GLint get_rings() { return _rings; }

	static geometry* Default;
};

class cylinder : public geometry 
{
protected:
	GLdouble _base;
	GLdouble _height;
	GLint _slices; 
	GLint _stacks;
public:
	cylinder(GLdouble base = 1.0, GLdouble height = 1.0, GLint slices = 30, GLint stacks = 1);
	inline virtual void setup(renderer* renderer) { renderer->render(this); }

	inline GLdouble get_base() { return _base; }
	inline GLdouble get_height() { return _height; }
	inline GLint get_slices() { return _slices; }
	inline GLint get_stacks() { return _stacks; }

	static geometry* Default;
};

class cone : public geometry 
{
protected:
	GLdouble _base;
	GLdouble _height;
	GLint _slices;
	GLint _stacks;
public:
	cone(GLdouble base = 1.0, GLdouble height = 1.0, GLint slices = 30, GLint stacks = 1);
	inline virtual void setup(renderer* renderer) { renderer->render(this); }

	inline GLdouble get_base() { return _base; }
	inline GLdouble get_height() { return _height; }
	inline GLint get_slices() { return _slices; }
	inline GLint get_stacks() { return _stacks; }

	static geometry* Default;
};

class tetrahedron : public geometry 
{
public:
	inline virtual void setup(renderer* renderer) { renderer->render(this); }

	static geometry* Default;
};

class hexahedron : public geometry
{
public:
	inline virtual void setup(renderer* renderer) { renderer->render(this); }

	static geometry* Default;
};
typedef hexahedron cube;

class octahedron : public geometry 
{
public:
	inline virtual void setup(renderer* renderer) { renderer->render(this); }

	static geometry* Default;
};

class dodecahedron : public geometry 
{
public:
	inline virtual void setup(renderer* renderer) { renderer->render(this); }

	static geometry* Default;
};

class icosahedron : public geometry 
{
public:
	inline virtual void setup(renderer* renderer) { renderer->render(this); }

	static geometry* Default;
};

class utah_teapot : public geometry 
{
public:
	inline virtual void setup(renderer* renderer) { renderer->render(this); }

	static geometry* Default;
};

#endif /* geometry_h */
