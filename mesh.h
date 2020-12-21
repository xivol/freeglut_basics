#pragma once
#include <vector>
#include "geometry.h"
#include "texture.h"


class vertex_data : public nested_data<vec3D> { 
protected: virtual void setup_data(vec3D* data, renderer* render); 
public:
	vertex_data(render_index_param* base_data = nullptr);
	vertex_data(std::vector<vec3D>& vertices, std::vector<GLint>& indices, 
		render_index_param* base_data = nullptr);
};


class normal_data : public nested_data<vec3D> { 
protected: virtual void setup_data(vec3D* data, renderer* render); 
public:
	normal_data(render_index_param* base_data = nullptr);
	normal_data(std::vector<vec3D>& normals, std::vector<GLint>& indices,
		render_index_param* base_data = nullptr);
};


class mesh : public geometry
{
protected:
	vertex_data _vertices;
	triangle_data<vec3D> _normals;

	uvmap* _uvmap = nullptr;
public:
	mesh() {}
	mesh(std::vector<vec3D>& vertices, std::vector<GLint>& indices);
	mesh(std::vector<vec3D>& vertices, std::vector<GLint>& indices, std::vector<vec3D>& normals, std::vector<GLint>& norm_indices, uvmap* default_uv = nullptr);
	virtual void setup(renderer* renderer);

	inline uvmap* get_uvmap() { return _uvmap; }
	virtual void set_uvmap(uvmap* uvmap);
};

class plot : public mesh
{
protected:
	typedef double (*fzxy)(double, double);
	void generate_mesh(fzxy f, double min_x, double min_y,
		double max_x, double max_y, int slices_x, int slices_y);
public:
	plot(fzxy f, double min_x, double min_y,
		double max_x, double max_y, int slices_x, int slices_y);
};

class plane : public plot 
{
public:
	plane(double min_x, double min_y,
		double max_x, double max_y, int slices_x, int slices_y);
};

