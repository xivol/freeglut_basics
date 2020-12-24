#ifndef glut_h
#define glut_h

#ifdef __APPLE__
    #include <OpenGL/OpenGL.h>
    #include <GLUT/GLUT.h>
#endif

#ifdef _WIN32
    #include "GL/glew.h"
    #include "GL/freeglut.h"
#endif

#include "renderer.h"
#include "viewport.h"
#include "scene.h"
#include "input.h"

class glut : public input_handler_delegate
{
	class global_input : public keyboard_handler
	{
	public: 
		static global_input Default;
		virtual void special(int key, int x, int y);
	};

	input_manager* _input = nullptr;
	viewport* _viewport = nullptr;
	renderer* _renderer = nullptr;
	scene* _scene = nullptr;
	
	glut(int* argcp, char** argv);

	void set_viewport(viewport* viewport) { _viewport = viewport; }
	void set_renderer(renderer* renderer) { _renderer = renderer; }
	void set_scene(scene* scene) { _scene = scene; }
	
	template <typename T>
	void add_input_handler(T* handler) {
		if (auto ih = dynamic_cast<input_handler*>(handler))
			_input->add_handler(ih);
	}
	
	void reshape(GLint width, GLint height);
	void display();

	void input_handler_did_finish(bool update_graphics);
	
	/// MARK: Static	

    static glut* Instance;

	static void Idle() { glut::Instance->_input->idle(); }
	static void Display() { glut::Instance->display(); }
	static void Reshape(int w, int h) { glut::Instance->reshape(w, h); }
	static void Visibility(int state) { glut::Instance->_input->visibility(state); }
	static void Close() { glut::Instance->_input->close(); }

	static void Special(int key, int x, int y) { glut::Instance->_input->special(key, x, y); }
	static void Keyboard(unsigned char key, int x, int y) { glut::Instance->_input->keyboard(key, x, y); }
	static void Mouse(int button, int state, int x, int y) { glut::Instance->_input->mouse(button, state, x, y); }
	static void Motion(int x, int y) { glut::Instance->_input->motion(x, y, true); }
	static void Entry(int state) { glut::Instance->_input->entry(state); }

public:
	static void Init(int* argcp, char** argv) { Instance = new glut(argcp, argv); }
	static int Version() { return  9999/*glutGet(GLUT_VERSION)*/; }

	static void Start(const char* title, GLint left, GLint top, scene* scene, renderer* render, viewport* projection);

	static void DrawSphere(double dRadius, GLint slices, GLint stacks, bool is_wire = false);
	static void DrawTorus(double dInnerRadius, double dOuterRadius, GLint nSides, GLint nRings, bool is_wire = false);
	static void DrawCylinder(double base, double height, GLint slices, GLint stacks, bool is_wire = false);
	static void DrawCone(double base, double height, GLint slices, GLint stacks, bool is_wire = false);

	static void DrawCube(double dSize, bool is_wire = false);
	static void DrawTetrahedron(bool is_wire = false);
	static void DrawOctahedron(bool is_wire = false);
	static void DrawDodecahedron(bool is_wire = false);
	static void DrawIcosahedron(bool is_wire = false);
	static void DrawRhombicDodecahedron(bool is_wire = false);

	static void DrawSierpinskiSponge(int num_levels, double offset[3], double scale, bool is_wire = false);
	static void DrawTeapot(double scale, bool is_wire = false);
};

#endif /* glut_h */
