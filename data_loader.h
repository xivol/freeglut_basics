#pragma once
#include <string>
#include <tuple>
#include "mesh.h"
#include "texture.h"

template <typename T>
class data_loader { public: virtual T* load() = 0; };

class obj_data_loader : public data_loader<mesh>
{
	enum data_types { Object, Vertex, Face, Normal, Texture };
	const std::string line_data[5] = { "o", "v", "f", "vn", "vt" };

	/// TODO: Replace string with char* tokens to speed up obj loading
	class tokenizer {
		std::string _delimeter;
		std::string& _source;
		bool _skip_empty;
	public: 
		tokenizer(std::string& source, std::string delim, bool skip_empty_tokens = true);
		std::string next();
		bool has_more();
	};

	std::string _fname;

	std::tuple<int, int, int> face_index_split(std::string s);
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
