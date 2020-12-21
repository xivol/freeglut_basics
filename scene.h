#pragma once
#include <vector>
#include "renderer.h"
#include "viewport.h"
#include "camera.h"
#include "shape.h"
#include "material.h"
#include "light.h"
#include "input.h"

class scene: public renderable
{
protected:
	color _background;
	camera* _camera = nullptr;
	std::vector<shape*> _objects;
	std::vector<light*> _lights;

public:
	scene(color background = color::CYAN);
	~scene();

	virtual void init(viewport* view, renderer* renderer);
	virtual void render(renderer* render);
};
