#pragma once
#include "renderer.h"

class material : public render_param, public render_index_param 
{
public: 
	virtual void setup(renderer* renderer) = 0;
	virtual void setup(GLuint index, renderer* renderer) = 0; 
};

class color : public material
{
protected:
	union rgba {
		GLfloat values[4];
		struct {
			GLfloat r;
			GLfloat g;
			GLfloat b;
			GLfloat a;
		};
	} _rgba = { 0,0,0,1 };
public:
	color(GLfloat red, GLfloat green, GLfloat blue, GLfloat alpha = 1);

	virtual void setup(renderer* renderer);
	virtual void setup(GLuint index, renderer* renderer);

	inline rgba get_value() { return _rgba; }

	static color BLACK;
	static color WHITE;
	static color RED;
	static color GREEN;
	static color BLUE;
	static color CYAN;
	static color YELLOW;
	static color MAGENTA;

	color operator*(double rhv);
	operator GLfloat*();
};

class phong : public material, public render_param, public render_index_param
{
protected:
	color _ambient = color::BLACK;
	color _diffuse = color::WHITE;
	color _specular = color::WHITE;
	color _emission = color::BLACK;
	GLfloat _shininess = 1;
public:
	phong(const color& color);
	phong(const color& ambient, const color& diffuse, const color& specular, const color& emission, GLfloat shininess);

	virtual void setup(renderer* renderer);
	virtual void setup(GLuint index, renderer* renderer);

	inline color& ambient() { return _ambient; }
	void set_ambient(const color& color);
	void set_ambient(GLfloat red, GLfloat green, GLfloat blue);
	
	inline color& diffuse() { return _diffuse; }
	void set_diffuse(const color& color);
	void set_diffuse(GLfloat red, GLfloat green, GLfloat blue);

	inline color& specular() { return _specular; }
	void set_specular(const color& color);
	void set_specular(GLfloat red, GLfloat green, GLfloat blue);
	
	inline color& emission() { return _emission; }
	void set_emission(const color& color);
	void set_emission(GLfloat red, GLfloat green, GLfloat blue);
	
	inline GLfloat& shininess() { return _shininess; }
	void set_shininess(GLfloat shininess);
};

class substance : public decorator<material>, public render_index_param, public render_param
{
public: 
	inline substance(material* base_mat) : decorator(base_mat) {}
	inline virtual void setup(renderer* renderer) { if (_base) _base->setup(renderer); }
	inline virtual void setup(GLuint index, renderer* renderer) { if (_base) _base->setup(index, renderer); }
};



