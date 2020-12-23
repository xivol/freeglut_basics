#include <vector>
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

std::tuple<int, int, int> obj_data_loader::face_index_split(const std::string& s)
{
	auto start = 0U;
	auto end = s.find("/");

	if (end == std::string::npos)
		return  std::tuple<int, int, int>(std::stoi(s), 0, 0);

	auto vertex = s.substr(start, end - start);

	start = end + 1;
	end = s.find("/", start);

	if (end == std::string::npos)
		return  std::tuple<int, int, int>(std::stoi(vertex), std::stoi(s.substr(start)), 0);

	auto texture = s.substr(start, end - start);
	auto normal = s.substr(end + 1);

	return std::tuple<int, int, int>(std::stoi(vertex),
		(texture.length() == 0) ? 0 : std::stoi(texture),
		std::stoi(normal));
}

obj_data_loader::obj_data_loader(const char* fname) : _fname(fname)
{}

mesh* obj_data_loader::load()
{
	std::ifstream file(_fname);

	texture_data* vt = nullptr;
	normal_data* vn = nullptr;
	vertex_data* vv  = new vertex_data(nullptr);
	
	std::vector<std::string> line_tokens;

	for (std::string line; std::getline(file, line); )
	{
		if (line.length() == 0) // empty line
			continue;
		if (line[0] == '#') // comment
			continue;

		std::istringstream input(line);
		line_tokens.clear();

		std::copy(std::istream_iterator<std::string>(input),
			std::istream_iterator<std::string>(),
			//std::ostream_iterator<std::string>(std::cout, " : "));
			std::back_inserter(line_tokens));

		if (line_tokens[0] == line_start[Vertex]) // vertices 
		{
			vec3D v = { 0,0,0,1 };
			v.x = std::stod(line_tokens[1]);
			v.y = std::stod(line_tokens[2]);
			v.z = std::stod(line_tokens[3]);

			vv->add_data(v);
		}
		else if (line_tokens[0] == line_start[Normal]) // normals 
		{
			if (!vn) vn = new normal_data(nullptr);

			vec3D n = { 0,0,0,1 };
			n.x = std::stod(line_tokens[1]);
			n.y = std::stod(line_tokens[2]);
			n.z = std::stod(line_tokens[3]);

			vn->add_data(n);
		}
		else if (line_tokens[0] == line_start[Texture]) // uvmaps
		{
			if (!vt) vt = new texture_data(nullptr);

			tex2D t = { 0,0,1 };
			t.u = std::stod(line_tokens[1]);
			t.v = std::stod(line_tokens[2]);
			
			vt->add_data(t);
		}
		else if (line_tokens[0] == line_start[Face]) // faces
		{
			auto index1 = face_index_split(line_tokens[1]);
			auto index2 = face_index_split(line_tokens[2]);
			auto index3 = face_index_split(line_tokens[3]);

			int a = std::get<0>(index1) - 1;
			int b = std::get<0>(index2) - 1;
			int c = std::get<0>(index3) - 1;
			
			vv->add_triangle(a, b, c);

			if (std::get<1>(index3) != 0)
			{
				int a = std::get<1>(index1) - 1;
				int b = std::get<1>(index2) - 1;
				int c = std::get<1>(index3) - 1;

				vt->add_triangle(a, b, c);
			}
			if (std::get<2>(index3) != 0)
			{
				int a = std::get<2>(index1) - 1;
				int b = std::get<2>(index2) - 1;
				int c = std::get<2>(index3) - 1;

				vn->add_triangle(a, b, c);
			}

			// not sure what kind of order should be here
			// triangle-fan cycle seems to work
			for (int i = 4; i < line_tokens.size(); ++i)
			{
				index2 = index3;
				index3 = face_index_split(line_tokens[i]);
				
				int a = std::get<0>(index1) - 1;
				int b = std::get<0>(index2) - 1;
				int c = std::get<0>(index3) - 1;

				vv->add_triangle(a, b, c);

				if (std::get<1>(index3) != 0)
				{
					int a = std::get<1>(index1) - 1;
					int b = std::get<1>(index2) - 1;
					int c = std::get<1>(index3) - 1;

					vt->add_triangle(a, b, c);
				}
				if (std::get<2>(index3) != 0)
				{
					int a = std::get<2>(index1) - 1;
					int b = std::get<2>(index2) - 1;
					int c = std::get<2>(index3) - 1;

					vn->add_triangle(a, b, c);
				}
			}
		}
	}

	return new mesh(vv, vn, vt);
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
