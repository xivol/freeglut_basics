#include "scene.h"
#include <algorithm>

scene::scene(color background) : _background(background)
{}

void scene::init(viewport* view, renderer* renderer)
{
	renderer->setup_background_color(&_background);
}

void scene::render(renderer* renderer)
{
	if (_camera) _camera->setup(renderer);

	for (size_t i = 0; i < _lights.size(); ++i)
		_lights[i]->setup(i, renderer);
	
	for (size_t i = 0; i < _objects.size(); ++i)
		_objects[i]->render(renderer);

}

scene::~scene()
{
	for (auto l = _lights.begin(); l != _lights.end(); ++l)
		delete *l;

	for (auto s = _objects.begin(); s != _objects.end(); ++s)
		delete *s;
}
