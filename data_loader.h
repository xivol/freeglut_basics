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

class image {
protected:
	size _size = { 0,0 };
	GLint _channels = 0;
	GLubyte* _data = nullptr;
public:
	image(GLubyte* data, GLsizei width, GLsizei height, GLint channels);
	virtual ~image();
	inline size& get_size() { return _size; }
	inline GLint get_channels() { return _channels; }
	inline GLubyte* get_data() { return _data; }
};

class image_loader :public data_loader<image> {
	std::string _fname;
public:
	image_loader(const char* fname);
	virtual image* load();

	static void dispose(image* image);
};
