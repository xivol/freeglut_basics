#include <tuple>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
#include "data_loader.h"
#include "math.h"

std::tuple<int, int, int> obj_data_loader::face_index_split(std::string s)
{
	tokenizer token = tokenizer(s, "/", false);
	
	auto vertex = token.next();

	auto texture = token.next();
	if (texture.empty()) texture = "0";

	auto normal = token.next();
	if (normal.empty()) normal = "0";

	return std::make_tuple(std::stoi(vertex), std::stoi(texture), std::stoi(normal));
}

obj_data_loader::obj_data_loader(const char* fname) : _fname(fname)
{}

mesh* obj_data_loader::load()
{
	std::ifstream file(_fname);

	texture_data* texCoords = nullptr;
	normal_data* normals = nullptr;
	vertex_data* vertices  = new vertex_data(nullptr);

	for (std::string line; std::getline(file, line); )
	{
		if (line.length() == 0) // empty line
			continue;
		if (line[0] == '#') // comment
			continue;

		tokenizer tokens = tokenizer(line, " ");
		std::string line_start = tokens.next();

		if (line_start == line_data[Vertex]) // vertices 
		{
			vec3D v = { 0,0,0,1 };
			v.x = std::stod(tokens.next());
			v.y = std::stod(tokens.next());
			v.z = std::stod(tokens.next());
			printf("%f, %f, %f", v.x, v.y, v.z);
			vertices->add_data(v);
		}
		else if (line_start == line_data[Normal]) // normals 
		{
			if (!normals) normals = new normal_data(nullptr);

			vec3D n = { 0,0,0,1 };
			n.x = std::stod(tokens.next());
			n.y = std::stod(tokens.next());
			n.z = std::stod(tokens.next());

			normals->add_data(n);
		}
		else if (line_start == line_data[Texture]) // uvmaps
		{
			if (!texCoords) texCoords = new texture_data(nullptr);

			tex2D t = { 0,0,1 };
			t.u = std::stod(tokens.next());
			t.v = std::stod(tokens.next());
			
			texCoords->add_data(t);
		}
		else if (line_start == line_data[Face]) // faces
		{
			auto index1 = face_index_split(tokens.next());
			auto index2 = face_index_split(tokens.next());
			auto index3 = face_index_split(tokens.next());

			int a = std::get<0>(index1) - 1;
			int b = std::get<0>(index2) - 1;
			int c = std::get<0>(index3) - 1;
			
			vertices->add_triangle(a, b, c);

			if (std::get<1>(index3) != 0)
			{
				int a = std::get<1>(index1) - 1;
				int b = std::get<1>(index2) - 1;
				int c = std::get<1>(index3) - 1;

				texCoords->add_triangle(a, b, c);
			}
			if (std::get<2>(index3) != 0)
			{
				int a = std::get<2>(index1) - 1;
				int b = std::get<2>(index2) - 1;
				int c = std::get<2>(index3) - 1;

				normals->add_triangle(a, b, c);
			}

			// not sure what kind of order should be here
			// triangle-fan cycle seems to work
			for (int i = 4; tokens.has_more(); ++i)
			{
				index2 = index3;
				index3 = face_index_split(tokens.next());
				
				int a = std::get<0>(index1) - 1;
				int b = std::get<0>(index2) - 1;
				int c = std::get<0>(index3) - 1;

				vertices->add_triangle(a, b, c);

				if (std::get<1>(index3) != 0)
				{
					int a = std::get<1>(index1) - 1;
					int b = std::get<1>(index2) - 1;
					int c = std::get<1>(index3) - 1;

					texCoords->add_triangle(a, b, c);
				}
				if (std::get<2>(index3) != 0)
				{
					int a = std::get<2>(index1) - 1;
					int b = std::get<2>(index2) - 1;
					int c = std::get<2>(index3) - 1;

					normals->add_triangle(a, b, c);
				}
			}
		}
	}

	return new mesh(vertices, normals, texCoords);
}



image::image(GLubyte* data, GLsizei width, GLsizei height, GLint channels)
{
	_size.width = width;
	_size.height = height;
	_channels = channels;
	_data = data;
}

image::~image()
{
	image_loader::dispose(this);
}


image_loader::image_loader(const char * fname) : _fname(fname)
{}

image* image_loader::load()
{
	GLubyte* data;
	GLsizei width;
	GLsizei height;
	GLint channels;

	stbi_set_flip_vertically_on_load(true);
	data = stbi_load(_fname.c_str(), &width, &height, &channels, 0);

	return new image(data, width, height, channels);
}

void image_loader::dispose(image * image)
{
	stbi_image_free(image->get_data());
}

obj_data_loader::tokenizer::tokenizer(std::string& source, std::string delim, bool skip_empty_tokens) :
	_source(source)
{
	_delimeter = delim;
	_skip_empty = skip_empty_tokens;
}

std::string obj_data_loader::tokenizer::next()
{
	auto pos = _source.find(_delimeter);
	if (pos == std::string::npos) return _source;

	while (pos == 0 && _skip_empty)
	{
		_source.erase(0, pos + _delimeter.length());
		pos = _source.find(_delimeter);
	}

	auto _next = _source.substr(0, pos);
	_source.erase(0, pos + _delimeter.length());
	return _next;
}

bool obj_data_loader::tokenizer::has_more()
{
	return !_source.empty();
}
