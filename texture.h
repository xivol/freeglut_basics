#pragma once
#include "renderer.h"
#include "geometry.h"
#include "material.h"

class image;

class texture {
    // https://learnopengl.com/Getting-started/Textures
protected:	
	image* _image = nullptr;
    GLuint* _id = nullptr;
public:
	inline texture(image* image) { _image = image; }
	inline GLuint get_id() { return *_id; }
	inline bool is_registered() { return _id; }
    virtual void setup(renderer* renderer); 
};

class textured_material : public substance
{
    texture* _texture = nullptr;
public:
    textured_material(image* img, material* mat);
    virtual void setup(renderer* renderer);
};

class texture_data : public nested_data<tex2D> {
protected: virtual void setup_data(tex2D* data, renderer* render);
public:
    texture_data(render_index_param* base_data = nullptr);
};


//class uvmap : public texture_data {
//protected:
//    texture* _texture = nullptr;
//public:
//    uvmap(std::vector<tex2D>& uv, std::vector<GLint>& indices, texture* texture, render_index_param* base_data = nullptr);
//};
