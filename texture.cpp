#include "texture.h"


void texture::setup(renderer* renderer)
{
    //glBindTexture(GL_TEXTURE_2D, _id);
    //glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB,
    //    _graphics.get_size().width, _graphics.get_size().height,
    //    0, GL_RGB, GL_UNSIGNED_BYTE,
    //    (void*) _graphics.get_data());
    //glGenerateMipmap(GL_TEXTURE_2D);
}

texture_data::texture_data(render_index_param* base_data) : nested_data(base_data)
{}

void texture_data::setup_data(tex2D* data, renderer* render)
{
    render->setup_vertex_tex_coord(data);
}

image::image(GLubyte* data, GLsizei width, GLsizei height, GLint channels)
{
    _size.width = width;
    _size.height = height;
    _channels = channels;
    _data = data;
}

uvmap::uvmap(std::vector<tex2D>& uv, std::vector<GLint>& indices, texture* texture, render_index_param* base_data) :
    texture_data(base_data)
{
    _texture = texture;
    set_data(uv);
    set_indices(indices);
}

textured_material::textured_material(texture* tex, material* mat) : substance(mat)
{
    _texture = tex;
}

void textured_material::setup(renderer* renderer)
{
    substance::setup(renderer);
    if (_texture) _texture->setup(renderer);
}
