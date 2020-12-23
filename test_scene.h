#pragma once
#include "scene.h"

class test_scene : public scene, public keyboard_handler
{
protected:
	virtual void special(int key, int x, int y);
	virtual void keyboard(unsigned char key, int x, int y);
	virtual void init(viewport* view, renderer* renderer);
public:
	test_scene(color background = color::BLACK);
};

class plot_scene : public test_scene
{
protected:
	virtual void init(viewport* view, renderer* renderer);
public:
	plot_scene(color background = color::BLACK);
};

class mesh_scene : public scene, public mouse_handler
{
	virtual void motion(int x, int y, bool is_active);
	virtual void keyboard(unsigned char key, int x, int y);
	virtual void init(viewport* view, renderer* renderer);
public:
	mesh_scene(color background = color::BLACK);
};
