#include "texture.h"


void texture::setup(renderer* renderer)
{
	if (!is_registered()) _id = renderer->register_texture(_image);

	renderer->setup_material(this);
}


texture_data::texture_data(render_index_param* base_data) : nested_data(base_data)
{}

void texture_data::setup_data(tex2D* data, renderer* render)
{
    render->setup_vertex_tex_coord(data);
}


textured_material::textured_material(image* img, material* mat) : substance(mat)
{
    _texture = new texture(img);
}

void textured_material::setup(renderer* renderer)
{
    substance::setup(renderer);
    if (_texture) _texture->setup(renderer);
}
