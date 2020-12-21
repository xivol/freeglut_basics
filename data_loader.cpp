#include "data_loader.h"
#include "math.h"
#include <vector>
#include <tuple>
#include <fstream>
#include <sstream>
#include <string>
#include <algorithm>
#include <iterator>

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

	//texture_data* vt = new texture_data(nullptr);
	//normal_data* vn  = new normal_data(vt);
	//vertex_data* vv  = new vertex_data(vn);

	std::vector<vec3D> vertices;
	std::vector<vec3D> normals;
	std::vector<tex2D> uv;
	std::vector<GLint> indices;
	std::vector<GLint> norm_indices;
	std::vector<GLint> uvmap_indices;
	
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

			//vv->add_data(v);
			vertices.push_back(v);
		}
		else if (line_tokens[0] == line_start[Normal]) // normals 
		{
			vec3D n = { 0,0,0,1 };
			n.x = std::stod(line_tokens[1]);
			n.y = std::stod(line_tokens[2]);
			n.z = std::stod(line_tokens[3]);

			//vn->add_data(n);
			normals.push_back(n);
		}
		else if (line_tokens[0] == line_start[Texture]) // uvmaps
		{
			tex2D t = { 0,0,1 };
			t.u = std::stod(line_tokens[1]);
			t.v = std::stod(line_tokens[2]);
			
			//vt->add_data(t);
			uv.push_back(t);
		}
		else if (line_tokens[0] == line_start[Face]) // faces
		{
			auto index1 = face_index_split(line_tokens[1]);
			auto index2 = face_index_split(line_tokens[2]);
			auto index3 = face_index_split(line_tokens[3]);

			indices.push_back(std::get<0>(index1) - 1);
			indices.push_back(std::get<0>(index2) - 1);
			indices.push_back(std::get<0>(index3) - 1);
			
			/*vv->add_triangle(
				std::get<0>(index1) - 1,
				std::get<0>(index2) - 1,
				std::get<0>(index3) - 1);*/

			if (std::get<1>(index3) != 0)
			{
				uvmap_indices.push_back(std::get<1>(index1) - 1);
				uvmap_indices.push_back(std::get<1>(index2) - 1);
				uvmap_indices.push_back(std::get<1>(index3) - 1);
			}
			if (std::get<2>(index3) != 0)
			{
				norm_indices.push_back(std::get<2>(index1) - 1);
				norm_indices.push_back(std::get<2>(index2) - 1);
				norm_indices.push_back(std::get<2>(index3) - 1);
			}

			// not sure what kind of order should be here
			// triangle-fan cycle seems to work
			for (int i = 4; i < line_tokens.size(); ++i)
			{
				index2 = index3;
				index3 = face_index_split(line_tokens[i]);
				
				indices.push_back(std::get<0>(index1) - 1);
				indices.push_back(std::get<0>(index2) - 1);
				indices.push_back(std::get<0>(index3) - 1);

				if (std::get<1>(index3) != 0)
				{
					uvmap_indices.push_back(std::get<1>(index1) - 1);
					uvmap_indices.push_back(std::get<1>(index2) - 1);
					uvmap_indices.push_back(std::get<1>(index3) - 1);
				}
				if (std::get<2>(index3) != 0)
				{
					norm_indices.push_back(std::get<2>(index1) - 1);
					norm_indices.push_back(std::get<2>(index2) - 1);
					norm_indices.push_back(std::get<2>(index3) - 1);
				}
			}
		}
	}

	uvmap* default_uv = new uvmap(uv, uvmap_indices, nullptr);

	return new mesh(vertices, indices, normals, norm_indices, default_uv);
}

texture* texture_loader::load()
{
	//data = stbi_load(filename, &width, &height, &nrChannels, 0);

	return nullptr;
}
