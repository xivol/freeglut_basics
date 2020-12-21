#include "glut.h"
#include "scene.h"

glut* glut::Instance = nullptr;

void glut::display()
{
    _renderer->render((scene*)_scene);
    glutSwapBuffers();
}

glut::glut(int* argcp, char** argv)
{
    glutInit(argcp, argv);
    _input = new input_manager(this);
}

void glut::input_handler_did_finish(bool update_graphics)
{
    if (update_graphics)
        glutPostRedisplay();
}

void glut::reshape(GLint width, GLint height)
{
    _viewport->set_size(width, height);
    _viewport->setup(_renderer);
    glutPostRedisplay();
}

void glut::global_input::special(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_F11:
        glutFullScreenToggle();
        break;
    }
}

void glut::Start(const char* title, GLint left, GLint top, scene* scene, renderer* render, viewport* projection)
{
    Instance->set_viewport(projection);
    Instance->set_scene(scene);
    Instance->set_renderer(render);

    Instance->add_input_handler(scene);
    Instance->add_input_handler(render);

    glutInitWindowSize(projection->get_size().width, projection->get_size().height);
    glutInitWindowPosition(left, top);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);

    glutCreateWindow(title);

    scene->init(projection, render);

    glutIdleFunc(glut::Idle);
    glutDisplayFunc(glut::Display);
    glutOverlayDisplayFunc(NULL);
    glutReshapeFunc(glut::Reshape);
    glutPositionFunc(NULL);
    glutVisibilityFunc(glut::Visibility);
    glutCloseFunc(glut::Close);

    glutKeyboardFunc(glut::Keyboard);
    glutKeyboardUpFunc(NULL);
    glutSpecialFunc(glut::Special);
    glutSpecialUpFunc(NULL);
    glutMouseFunc(glut::Mouse);
    glutMouseWheelFunc(NULL);
    glutMotionFunc(glut::Motion);
    glutPassiveMotionFunc(NULL);
    glutEntryFunc(glut::Entry);

    glutMainLoop();
}

void glut::DrawSphere(double dRadius, GLint slices, GLint stacks, bool is_wire)
{
    auto sphere = (is_wire) ? &glutWireSphere : &glutSolidSphere;
    sphere(dRadius, slices, stacks);
}

void glut::DrawTorus(double dInnerRadius, double dOuterRadius, GLint nSides, GLint nRings, bool is_wire)
{
    auto torus = (is_wire) ? glutWireTorus : glutSolidTorus;
    torus(dInnerRadius, dOuterRadius, nSides, nRings);
}

void glut::DrawCylinder(double base, double height, GLint slices, GLint stacks, bool is_wire)
{
    auto cylinder = (is_wire) ? glutWireCylinder : glutSolidCylinder;
    cylinder(base, height, slices, stacks);
}

void glut::DrawCone(double base, double height, GLint slices, GLint stacks, bool is_wire)
{
    auto cone = (is_wire) ? &glutWireCone : &glutSolidCone;
    cone(base,height, slices, stacks);
}

void glut::DrawCube(double dSize, bool is_wire)
{
    auto cube = (is_wire) ? &glutWireCube : &glutSolidCube;
    cube(dSize);
}

void glut::DrawTetrahedron(bool is_wire)
{
    auto terah = (is_wire) ? &glutWireTetrahedron: &glutSolidTetrahedron;
    terah();
}

void glut::DrawOctahedron(bool is_wire)
{
    auto octah = (is_wire) ? &glutWireOctahedron : &glutSolidOctahedron;
    octah();
}

void glut::DrawDodecahedron(bool is_wire)
{
    auto dodecah = (is_wire) ? &glutWireDodecahedron : &glutSolidDodecahedron;
    dodecah();
}

void glut::DrawIcosahedron(bool is_wire)
{
    auto icosah = (is_wire) ? &glutWireIcosahedron : &glutSolidIcosahedron;
    icosah();
}

void glut::DrawRhombicDodecahedron(bool is_wire)
{
    auto rdodecah = (is_wire) ? &glutWireRhombicDodecahedron : &glutSolidRhombicDodecahedron;
    rdodecah();
}

void glut::DrawSierpinskiSponge(int num_levels, double offset[3], double scale, bool is_wire)
{
    auto ssponge = (is_wire) ? &glutWireSierpinskiSponge : &glutSolidSierpinskiSponge;
    ssponge(num_levels, offset, scale);
}

void glut::DrawTeapot(double scale, bool is_wire)
{
    auto teapot = (is_wire) ? &glutWireTeapot : &glutSolidTeapot;
    teapot(scale);
}
