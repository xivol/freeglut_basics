#pragma once
#include "renderer.h"
#include "geometry.h"
#include "material.h"


class image {
protected:
    size _size = { 0,0 };
    GLint _channels = 0;
    GLubyte* _data = nullptr;
public:
    image(GLubyte* data, GLsizei width, GLsizei height, GLint channels);
    inline size get_size() { return _size; }
    inline GLint get_channels() { return _channels; }
};


class texture : public image {
    // https://learnopengl.com/Getting-started/Textures
protected:
    GLenum _wrapping = 0;
    GLenum _filtering = 0;
    GLenum _mipmaps = 0;
    GLuint _id = 0;
public:
    inline texture(GLubyte* data, GLsizei width, GLsizei height, GLint channels) : 
        image(data, width, height, channels) {}
    virtual void setup(renderer* renderer); 
};

class textured_material : public substance
{
    texture* _texture = nullptr;
public:
    textured_material(texture* tex, material* mat);
    virtual void setup(renderer* renderer);
};

class texture_data : public nested_data<tex2D> {
protected: virtual void setup_data(tex2D* data, renderer* render);
public:
    texture_data(render_index_param* base_data);
};


class uvmap : public texture_data {
protected:
    texture* _texture = nullptr;
public:
    uvmap(std::vector<tex2D>& uv, std::vector<GLint>& indices, texture* texture, render_index_param* base_data = nullptr);
};

