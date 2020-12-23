#pragma once
#include "math.h"
#include "input.h"

class renderer;

template <typename T>
class decorator : public T
{
protected:
    T* _base = nullptr;
public:
    inline decorator(T* base) { _base = base; }
	inline T* reset_base(T* base) { auto t = _base; _base = base;  return t; }
};

class render_param { public: virtual void setup(renderer* renderer) = 0; };

class render_index_param { public: virtual void setup(GLuint index, renderer* renderer) = 0; };

class renderable { public: virtual void render(renderer* renderer) = 0; };

class viewport; class perspective;
class camera;
class point; class oriented; class extended;
class point_light; class attenuated_light; class directional_light; class spotlight_light;
class color; class phong;
class geometry; class sphere; class torus; class cone; class cylinder; class utah_teapot;
class tetrahedron; class hexahedron; class octahedron; class dodecahedron; class icosahedron;
class image; class texture;
class scene;

enum class render_mode { Solid, Wireframe };

class renderer : public keyboard_handler
{
protected:
    render_mode _mode = render_mode::Solid;
public:
    inline render_mode get_render_mode() const { return _mode; }
    virtual void set_render_mode(render_mode mode);

    virtual void special(int key, int x, int y);
    
    virtual void setup_background_color(color* c) const = 0;

	virtual void setup_viewport(viewport* viewport) const = 0;
    
    virtual void setup_projection_begin() const = 0;
    virtual void setup_projection(perspective* perspective) const = 0;

    virtual void setup_view_begin() const = 0;
    virtual void setup_view_look_at(camera* camera) const = 0;

    virtual void local_world_begin() const = 0;
    virtual void setup_world(point* pos) const = 0;
    virtual void setup_world(oriented* rot) const = 0;
    virtual void setup_world(extended* scl) const = 0;
    virtual void local_world_end() const = 0;

    virtual void setup_light(GLuint index, GLboolean is_on) const = 0;
    virtual void setup_light(GLuint index, attenuated_light* l) const = 0;
    virtual void setup_light(GLuint index, point_light* l) const = 0;
    virtual void setup_light(GLuint index, directional_light* l) const = 0;
    virtual void setup_light(GLuint index, spotlight_light* l) const = 0;
    virtual void setup_light(GLuint index, color* c) const = 0;
    virtual void setup_light(GLuint index, phong* ph) const = 0;

    virtual void setup_material(phong* ph) const = 0;
    //virtual void setup_material_shader() const = 0;
	virtual void setup_material(texture* t) const = 0;
    
    //virtual void setup_geometry_mesh(mesh* m) const = 0;
    virtual void render_begin(geometry* g) const = 0;
    virtual void setup_vertex_position(vec3D* pos) const = 0;
    virtual void setup_vertex_normal(vec3D* nor) const = 0;
    virtual void setup_vertex_color(color* col) const = 0;
    virtual void setup_vertex_tex_coord(tex2D* tex) const = 0;
    virtual void render_end() const = 0;

	virtual GLuint* register_texture(image* img) const = 0;

    virtual void render(scene* scene) = 0;

    virtual void render(sphere* sphere) const = 0;
    virtual void render(torus* torus) const = 0;
    virtual void render(cone* cone) const = 0;
    virtual void render(cylinder* cylinder) const = 0;

    virtual void render(tetrahedron* tet) const = 0;
    virtual void render(hexahedron* hex) const = 0;
    virtual void render(octahedron* oct) const = 0;
    virtual void render(dodecahedron* dod) const = 0;
    virtual void render(icosahedron* ico) const = 0;
    virtual void render(utah_teapot* teapot) const = 0;
};


class opengl_renderer : public renderer
{
public:
    virtual void setup_background_color(color* c) const;

    virtual void setup_viewport(viewport* viewport) const;
    
    virtual void setup_projection_begin() const;
    virtual void setup_projection(perspective* perspective) const;
    
    virtual void setup_view_begin() const;
    virtual void setup_view_look_at(camera* camera) const;

    virtual void local_world_begin() const;
    virtual void setup_world(point* pos) const;
    virtual void setup_world(oriented* rot) const;
    virtual void setup_world(extended* scl) const;
    virtual void local_world_end() const;

	
    virtual void setup_material(phong* ph) const;
	virtual void setup_material(texture* tex) const;

    virtual void render_begin(geometry* g) const;
    virtual void setup_vertex_position(vec3D* pos) const;
    virtual void setup_vertex_normal(vec3D* nor) const;
    virtual void setup_vertex_color(color* col) const;
    virtual void setup_vertex_tex_coord(tex2D* tex) const ;
    virtual void render_end() const;

    virtual void setup_light(GLuint index, GLboolean is_on) const;
    virtual void setup_light(GLuint index, attenuated_light* l) const;
    virtual void setup_light(GLuint index, point_light* l) const;
    virtual void setup_light(GLuint index, directional_light* l) const;
    virtual void setup_light(GLuint index, spotlight_light* l) const;
    virtual void setup_light(GLuint index, color* c) const;
    virtual void setup_light(GLuint index, phong* ph) const;

	virtual GLuint* register_texture(image* img) const;
	
	virtual void render(scene* scene);

    virtual void render(sphere* sphere) const;
    virtual void render(torus* torus) const;
    virtual void render(cone* cone) const;
    virtual void render(cylinder* cylinder) const;

    virtual void render(tetrahedron* tet) const;
    virtual void render(hexahedron* hex) const;
    virtual void render(octahedron* oct) const;
    virtual void render(dodecahedron* dod) const;
    virtual void render(icosahedron* ico) const;
    virtual void render(utah_teapot* teapot) const;
};
