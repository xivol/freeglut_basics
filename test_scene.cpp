#include "test_scene.h"
#include "camera.h"
#include "mesh.h"
#include "data_loader.h"
#include "texture.h"
#include <algorithm>


test_scene::test_scene(color background) : scene(background)
{}

void test_scene::init(viewport* view, renderer* renderer)
{
	scene::init(view,renderer);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, color::BLACK);

	_camera = new camera(0, 0, 100, 0, 0, 0, 0, 1, 0);

	std::vector<substance*> mat = { 
		new substance(&color::BLUE), new substance(&color::RED) , 
		new substance(&color::GREEN), new substance(&color::YELLOW),
		new substance(&color::CYAN), new substance(&color::MAGENTA), 
		new substance(&color::WHITE) 
	};

	int count = 6;
	double angle = 6.283 / count;
	double radius = 10;
	for(int j = 0; j < count; ++j)
	for (int i = 0; i < count; ++i)
	{
		double x = 2 * radius * (i + 0.5 - count * 0.5);
		double y = 2 * radius * (j + 0.5 - count * 0.5);
		
		geometry* g = nullptr;
		switch ((j * count + i)%10) {
		case 0:
			g = sphere::Default;
			break;
		case 1:
			g = cube::Default;
			break;
		case 2:
			g = cylinder::Default;
			break;
		case 3:
			g = tetrahedron::Default;
			break;
		case 4:
			g = octahedron::Default;
			break;
		case 5:
			g = torus::Default;
			break;
		case 6:
			g = dodecahedron::Default;
			break;
		case 7:
			g = cone::Default;
			break;
		case 8:
			g = icosahedron::Default;
			break;
		case 9:
			g = utah_teapot::Default;
			break;
		}
		
		shape* s = new shape(g, mat[(i + j) % mat.size()], x, y, 0);
		if (dynamic_cast<dodecahedron*>(g))
			s->set_scale(radius / 3, radius / 3, radius / 3);
		else
			s->set_scale(radius / 2, radius / 2, radius / 2);
		s->set_rotation(30, 30, 30);

		_objects.push_back(s);
	}

	_lights.push_back(new point_light(&color::YELLOW, 0, 0, 20));
	_lights.push_back(new spotlight_light(&color::CYAN, 0, 0, 40, 0, 0, -1, 45));
	_lights.push_back(new directional_light(&color::MAGENTA, 0, 0, 40, 0, 0, -1));
}

void test_scene::special(int key, int x, int y)
{
	auto l = *std::find_if(_lights.begin(), _lights.end(), [](auto ll) {return ll->is_on(); });
	auto spotlight = dynamic_cast<spotlight_light*>(l);
	auto point = dynamic_cast<point_light*>(l);
	auto directional = dynamic_cast<directional_light*>(l);

	bool has_changes = true;
	switch (key)
	{
	case GLUT_KEY_UP:
		if (spotlight)
			spotlight->translate_target_by(0, 0.1, 0);
		else if (point)
			point->translate_by(0, 1, 0);
		else if (directional)
			directional->translate_by(0, 1, 0);
		break;
	case GLUT_KEY_DOWN:
		if (spotlight)
			spotlight->translate_target_by(0, -0.1, 0);
		else if (point)
			point->translate_by(0, -1, 0);
		else if (directional)
			directional->translate_by(0, -1, 0);
		break;
	case GLUT_KEY_RIGHT:
		if (spotlight)
			spotlight->translate_target_by(0.1, 0, 0);
		else if (point)
			point->translate_by(1, 0, 0);
		else if (directional)
			directional->translate_by(1, 0, 0);
		break;
	case GLUT_KEY_LEFT:
		if (spotlight)
			spotlight->translate_target_by(-0.1, 0, 0);
		else if (point)
			point->translate_by(-1, 0, 0);
		else if (directional)
			directional->translate_by(-1, 0, 0);
		break;
	case GLUT_KEY_PAGE_UP:
		if (spotlight)
			spotlight->rotate_by(0, 0, -1);
		else if (point)
			point->translate_by(0, 0, 1);
		else if (directional)
			directional->rotate_by(0, 0, -1);
		break;
	case GLUT_KEY_PAGE_DOWN:
		if (spotlight)
			spotlight->rotate_by(0, 0, 1);
		else if (point)
			point->translate_by(0, 0, -1);
		else if (directional)
			directional->rotate_by(0, 0, 1);
		break;
	default:
		has_changes = false;
		break;
	}

	_input_delegate->input_handler_did_finish(has_changes);
}

void test_scene::keyboard(unsigned char key, int x, int y)
{
	bool has_changes = true;
	switch (key) {
	case '1':
		if (_lights[0]->is_on()) _lights[0]->set_on(false);
		else _lights[0]->set_on(true);
		break;
	case '2':
		if (_lights[1]->is_on()) _lights[1]->set_on(false);
		else _lights[1]->set_on(true);
		break;
	case '3':
		if (_lights[2]->is_on()) _lights[2]->set_on(false);
		else _lights[2]->set_on(true);
		break;
	default:
		has_changes = false;
		break;
	}
	_input_delegate->input_handler_did_finish(has_changes);
}

void plot_scene::init(viewport* view, renderer* renderer)
{
	scene::init(view, renderer);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, color::BLACK);

	_camera = new camera(0, 0, 100, 0, 0, 0, 0, 1, 0);

	auto plot1 = new shape(
		new plot([](double x, double y) { return 50 * sin(sqrt(x * x + y * y + 9)) / sqrt(x * x + y * y + 9); }, 
		//new plane(
			-50, -50, 50, 50, 100, 100),
		new substance(&color::WHITE),
		0, 0, 1);
	plot1->set_rotation(-45, 0, 0);
	_objects.push_back(plot1);

	_lights.push_back(new point_light(&color::YELLOW, 0, 0, 20));
	_lights.push_back(new spotlight_light(&color::CYAN, 0, 0, 40, 0, 0, -1, 45, 0.5));
	_lights.push_back(new directional_light(&color::MAGENTA, 0, 0, 40, 0, 0, -1));
}

plot_scene::plot_scene(color background) : test_scene(background) 
{}


void mesh_scene::motion(int x, int y, bool is_active)
{
	static int prev_x;
	static int prev_y;
	if (is_active) 
	{
		_objects[0]->rotate_by((y - prev_y), 0, (x - prev_x));
		prev_y = y;
		prev_x = x;

		_input_delegate->input_handler_did_finish(true);
	}
}

void mesh_scene::keyboard(unsigned char key, int x, int y)
{
}

void mesh_scene::init(viewport* view, renderer* renderer)
{
	scene::init(view, renderer);

	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
	glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, color::BLACK);
	glEnable(GL_TEXTURE_2D);

	_camera = new camera(0, 0, 100, 0, 0, 0, 0, 1, 0);

	auto obj = new shape(
		obj_data_loader("C:\\Users\\aurgt\\source\\repos\\freeglut_basics\\data\\12140_Skull_v3_L2.obj").load(),
		new textured_material(image_loader("C:\\Users\\aurgt\\source\\repos\\freeglut_basics\\data\\Skull.jpg").load(),
			new phong(color::WHITE*0.1, color::YELLOW, color::WHITE, color::BLACK, 128)),
		0, 0, -10);
	obj->set_scale(2, 2, 2);
	_objects.push_back(obj);

	_lights.push_back(new point_light(&color::WHITE, 0, 0, 100));
}

mesh_scene::mesh_scene(color background) : scene(background)
{}
