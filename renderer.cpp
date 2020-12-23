#include "GL/glew.h"
#include "GL/freeglut.h"
#include "glut.h"
#include "data_loader.h"
#include "renderer.h"
#include "viewport.h"
#include "camera.h"
#include "material.h"
#include "texture.h"
#include "scene.h"

void renderer::set_render_mode(render_mode mode)
{
	_mode = mode;
}

void renderer::special(int key, int x, int y)
{
    switch (key)
    {
    case GLUT_KEY_F10:
        set_render_mode(static_cast<render_mode>((static_cast<int>(_mode) + 1) % 2));
        _input_delegate->input_handler_did_finish(true);
        break;
    }
}

void opengl_renderer::setup_global_defaults() const
{
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_LIGHTING);
	glEnable(GL_TEXTURE_2D);
	glEnable(GL_NORMALIZE);
	glEnable(GL_COLOR_MATERIAL);
}

void opengl_renderer::setup_background_color(color* c) const
{
    glClearColor(c->get_value().r, c->get_value().g, c->get_value().b, c->get_value().a);
}

void opengl_renderer::setup_viewport(viewport* v) const
{
    glViewport(0, 0, v->get_size().width, v->get_size().height);
}

void opengl_renderer::setup_projection_begin() const
{
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
}

void opengl_renderer::setup_projection(perspective* p) const
{
    if(p) gluPerspective(p->get_fov(),
        (GLdouble)p->get_size().width / (GLdouble)p->get_size().height,
        p->get_clipping().near_plane, p->get_clipping().far_plane);
}

void opengl_renderer::setup_view_begin() const
{
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void opengl_renderer::setup_view_look_at(camera* camera) const
{

    if (camera) gluLookAt(
        camera->get_position().x, camera->get_position().y, camera->get_position().z,
        camera->get_target().x, camera->get_target().y, camera->get_target().z,
        camera->get_up().x, camera->get_up().y, camera->get_up().z);
}

void opengl_renderer::local_world_begin() const
{
    glPushMatrix();
}

void opengl_renderer::setup_world(point* pos) const
{
    glTranslatef(pos->get_position().x, pos->get_position().y, pos->get_position().z);
}

void opengl_renderer::setup_world(oriented* rot) const
{
    glRotatef(rot->get_rotation().x, 1, 0, 0);
    glRotatef(rot->get_rotation().y, 0, 1, 0);
    glRotatef(rot->get_rotation().z, 0, 0, 1);
}

void opengl_renderer::setup_world(extended* scl) const
{
    glScalef(scl->get_scale().x, scl->get_scale().y, scl->get_scale().z);
}

void opengl_renderer::local_world_end() const
{
    glPopMatrix();
}

void opengl_renderer::setup_material(phong* ph) const
{
    glMaterialfv(GL_FRONT, GL_AMBIENT, ph->ambient());
    glMaterialfv(GL_FRONT, GL_DIFFUSE, ph->diffuse());
    glMaterialfv(GL_FRONT, GL_SPECULAR, ph->specular());
    glMaterialfv(GL_FRONT, GL_EMISSION, ph->emission());
    glMaterialf(GL_FRONT, GL_SHININESS, ph->shininess());
}

void opengl_renderer::setup_material(texture* tex) const
{
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, tex->get_id());
}

void opengl_renderer::render_begin(geometry* g) const
{
    glPolygonMode(GL_FRONT_AND_BACK, 
        (_mode == render_mode::Wireframe) ? GL_LINE : GL_FILL);

    glBegin(GL_TRIANGLES);
}

void opengl_renderer::setup_vertex_position(vec3D* pos) const
{
    glVertex3fv(*pos);
}

void opengl_renderer::setup_vertex_normal(vec3D* nor) const
{
    glNormal3fv(*nor);
}

void opengl_renderer::setup_vertex_color(color* col) const
{
    glColor3fv(*col);
}

void opengl_renderer::setup_vertex_tex_coord(tex2D* tex) const
{
    glTexCoord2fv(*tex);
}

void opengl_renderer::render_end() const
{
    glEnd();
}

void opengl_renderer::setup_light(GLuint index, GLboolean is_on) const
{
    if (is_on) glEnable(GL_LIGHT0 + index);
    else glDisable(GL_LIGHT0 + index);
}

void opengl_renderer::setup_light(GLuint index, attenuated_light* l) const
{
    glLightf(GL_LIGHT0 + index, GL_CONSTANT_ATTENUATION, l->get_attenuation()[0]);
    glLightf(GL_LIGHT0 + index, GL_LINEAR_ATTENUATION, l->get_attenuation()[1]);
    glLightf(GL_LIGHT0 + index, GL_QUADRATIC_ATTENUATION, l->get_attenuation()[2]);
}

void opengl_renderer::setup_light(GLuint index, point_light* l) const
{
    glLightfv(GL_LIGHT0 + index, GL_POSITION, l->get_position());
}

void opengl_renderer::setup_light(GLuint index, directional_light* l) const
{
    vec3D dir = -l->get_direction(); dir.w = 0;
    glLightfv(GL_LIGHT0 + index, GL_POSITION, dir);
}

void opengl_renderer::setup_light(GLuint index, spotlight_light* l) const
{
    glLightfv(GL_LIGHT0 + index, GL_POSITION, l->get_position());
    glLightfv(GL_LIGHT0 + index, GL_SPOT_DIRECTION, l->get_direction());
    glLightf(GL_LIGHT0 + index, GL_SPOT_CUTOFF, l->get_cutoff());
    glLightf(GL_LIGHT0 + index, GL_SPOT_EXPONENT, l->get_exponent());
}

void opengl_renderer::setup_light(GLuint index, color* c) const
{
    glLightfv(GL_LIGHT0 + index, GL_AMBIENT, (*c) * 0.1);
    glLightfv(GL_LIGHT0 + index, GL_DIFFUSE, *c);
    glLightfv(GL_LIGHT0 + index, GL_SPECULAR, color::WHITE);
}

void opengl_renderer::setup_light(GLuint index, phong* ph) const
{
    glLightfv(GL_LIGHT0 + index, GL_AMBIENT, ph->ambient());
    glLightfv(GL_LIGHT0 + index, GL_DIFFUSE, ph->diffuse());
    glLightfv(GL_LIGHT0 + index, GL_SPECULAR, ph->specular());
}

void opengl_renderer::setup_light_global_ambient(color * c) const
{
	glLightModelfv(GL_LIGHT_MODEL_AMBIENT, *c);
}

GLuint* opengl_renderer::register_texture(image * img) const
{
	GLuint* id = new GLuint;
	glGenTextures(1, id);
	glBindTexture(GL_TEXTURE_2D, *id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	//glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP, GL_TRUE);
	auto depth = img->get_channels() == 4 ? GL_RGBA : GL_RGB;

	glTexImage2D(GL_TEXTURE_2D, 0, depth, 
		img->get_size().width, img->get_size().height, 
		0, depth, GL_UNSIGNED_BYTE, img->get_data());
	glGenerateMipmap(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, 0);
	delete img;
	return id;
}

void opengl_renderer::render(scene* scene)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    
    scene->render(this);
    
    glFlush();
}

void opengl_renderer::render(sphere* sphere) const
{
    glut::DrawSphere(sphere->get_radius(), sphere->get_slices(), 
        sphere->get_stacks(), _mode == render_mode::Wireframe);
}

void opengl_renderer::render(torus* torus) const
{
    glut::DrawTorus(torus->get_inner_radius(), torus->get_outer_radius(),
        torus->get_sides(), torus->get_rings(), _mode == render_mode::Wireframe);
}

void opengl_renderer::render(cone* cone) const
{
    glut::DrawCone(cone->get_base(), cone->get_height(),
        cone->get_slices(), cone->get_stacks(), _mode == render_mode::Wireframe);
}

void opengl_renderer::render(cylinder* cylinder) const
{
    glut::DrawCylinder(cylinder->get_base(), cylinder->get_height(),
        cylinder->get_slices(), cylinder->get_stacks(), _mode == render_mode::Wireframe);
}

void opengl_renderer::render(tetrahedron* tet) const
{
    glut::DrawTetrahedron(_mode == render_mode::Wireframe);
}

void opengl_renderer::render(hexahedron* hex) const
{
    glut::DrawCube(1, _mode == render_mode::Wireframe);
}

void opengl_renderer::render(octahedron* oct) const
{
    glut::DrawOctahedron(_mode == render_mode::Wireframe);
}

void opengl_renderer::render(dodecahedron* dod) const
{
    glut::DrawDodecahedron(_mode == render_mode::Wireframe);
}

void opengl_renderer::render(icosahedron* ico) const
{
    glut::DrawIcosahedron(_mode == render_mode::Wireframe);
}

void opengl_renderer::render(utah_teapot* teapot) const
{
    glut::DrawTeapot(1, _mode == render_mode::Wireframe);
}
