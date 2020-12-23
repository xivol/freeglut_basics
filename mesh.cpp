#include "mesh.h"
#include <algorithm>
#include <exception>


mesh::~mesh()
{
	delete _vertices;
	delete _normals;
	delete _uvmap;
}

mesh::mesh(vertex_data * vertices, normal_data * normals, texture_data * uvmap)
{
	_vertices = vertices;
	
	if (normals && normals->size() ==_vertices->size())
	{
		_normals = normals;
		auto t = _vertices->reset_base(_normals);
		delete t;
	} 
	
	_uvmap = uvmap;
	if (uvmap && uvmap->size() == _vertices->size())
	{
		auto t = _normals->reset_base(_uvmap);
		delete t;
	}
}

void mesh::setup(renderer* renderer)
{
	renderer->render_begin(this);
	
	for (int i = 0; i < _vertices->size(); ++i)
		_vertices->setup(i, renderer);

	renderer->render_end();
}

void plot::generate_mesh(fzxy f, double min_x, double min_y, double max_x, double max_y, int slices_x, int slices_y)
{
	double step_x = (max_x - min_x) / slices_x;
	double step_y = (max_y - min_y) / slices_y;
	std::vector<vec3D> t_normals;
	_vertices = new vertex_data();
	_normals = new normal_data();

	for (double x = min_x; x < max_x + step_x; x += step_x)
		for (double y = min_y; y < max_y + step_x; y += step_y)
		{
			vec3D vertex = { x,y,f(x, y),1 };
			_vertices->add_data(vertex);
			vec3D normal = { 0,0,0,1 };
			t_normals.push_back(normal);

			int len = slices_x + 1;
			int id = _vertices->get_data().size() - 1;
			int col_id = id / len, row_id = id % len;

			if (col_id > 0 && row_id > 0)
			{
				//  d -- b
				//  | \\ |
				//  c -- a
				int a = col_id * len + row_id;
				int b = col_id * len + row_id - 1;
				int c = (col_id - 1) * len + row_id;
				int d = (col_id - 1) * len + row_id - 1;

				_vertices->add_triangle(a, b, d);
				_vertices->add_triangle(a, d, c);

				vec3D t1_n = (_vertices->get_data(a) - _vertices->get_data(b)).cross(
					_vertices->get_data(d) - _vertices->get_data(b));
				t_normals[a] += t1_n;
				t_normals[b] += t1_n;
				t_normals[d] += t1_n;
				_normals->add_triangle(a, b, d);

				vec3D t2_n = (_vertices->get_data(a) - _vertices->get_data(d)).cross(
					_vertices->get_data(c) - _vertices->get_data(d));
				t_normals[a] += t2_n;
				t_normals[d] += t2_n;
				t_normals[c] += t2_n;
				_normals->add_triangle(a, d, c);
			}
		}

	for (vec3D& n : t_normals)
	{
		_normals->add_data(n.normalized());
	}
	
}

plot::plot(fzxy f, double min_x, double min_y, double max_x, double max_y, int slices_x, int slices_y)
{
	generate_mesh(f, min_x, min_y, max_x, max_y, slices_x, slices_y);
	_vertices->reset_base(_normals);
}

plane::plane(double min_x, double min_y, double max_x, double max_y, int slices_x, int slices_y) :
	plot([](double x, double y) { return 0.0; }, min_x, min_y, max_x, max_y, slices_x, slices_y)
{}

vertex_data::vertex_data(render_index_param* base_data): nested_data(base_data)
{}

vertex_data::vertex_data(std::vector<vec3D>& vertices, std::vector<GLint>& indices,
	render_index_param* base_data) : nested_data(base_data)
{}

void vertex_data::setup_data(vec3D* data, renderer* render)
{
	render->setup_vertex_position(data);
}

normal_data::normal_data(render_index_param* base_data) : nested_data(base_data)
{}

normal_data::normal_data(std::vector<vec3D>& normals, std::vector<GLint>& indices,
	render_index_param* base_data) : nested_data(base_data)
{}

void normal_data::setup_data(vec3D* data, renderer* render)
{
	render->setup_vertex_normal(data);
}
