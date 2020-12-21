#pragma once
#include <string>
#include <tuple>
#include "mesh.h"
#include "texture.h"

template <typename T>
class data_loader { public: virtual T* load() = 0; };

class obj_data_loader : public data_loader<mesh>
{
	enum data_types { Vertex, Face, Normal, Texture };
	const std::string line_start[4] = { "v", "f", "vn", "vt" };

	std::string _fname;

	std::tuple<int, int, int> face_index_split(const std::string& s);
public:
	obj_data_loader(const char* fname);

	virtual mesh* load();
};

class texture_loader :public data_loader<texture> {
	std::string _fname;
public:
	texture_loader(const char* fname);
	virtual texture* load();
};
