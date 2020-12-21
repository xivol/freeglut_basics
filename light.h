#pragma once
#ifndef light_h
#define light_h
#include "world_transform.h"
#include "material.h"

class light : public substance, public render_index_param
{
protected:
    GLboolean _is_on = true;
public:
    light(material* mat);
    ~light();

    inline bool is_on() const { return _is_on; }
    inline void set_on(GLboolean is_on) { _is_on = is_on; }
    virtual void setup(GLuint index, renderer* renderer);
};

class attenuated_light : public light
{
protected:
    GLfloat _attenuation[3] = { 1,0.01,0.0001 };
public:
    attenuated_light(material* mat);
    virtual void setup(GLuint index, renderer* renderer);

    inline GLfloat* get_attenuation() { return _attenuation; }
    virtual void set_attenuation(GLfloat constant, GLfloat linear, GLfloat quadratic);
};

class point_light : public point, public attenuated_light 
{
public:
    point_light(material* mat, GLfloat x, GLfloat y, GLfloat z);
    virtual void setup(GLuint index, renderer* renderer);
};

class spotlight_light: public directional, public attenuated_light
{
protected:
    GLfloat _cutoff = 180;
    GLfloat _exponent = 0;
public:
    spotlight_light(material* mat, GLfloat x, GLfloat y, GLfloat z, 
        GLfloat dx=0, GLfloat dy=0, GLfloat dz=-1, GLfloat cutoff = 90, GLfloat exponent = 0.1);
    virtual void setup(GLuint index, renderer* renderer);

    inline GLfloat get_cutoff() { return _cutoff; }
    virtual void set_cutoff(GLfloat cutoff);

    inline GLfloat get_exponent() { return _exponent; }
    virtual void set_exponent(GLfloat exponent);
};

class directional_light: public directional, public light 
{
public:
    directional_light(material* mat, GLfloat x, GLfloat y, GLfloat z,
        GLfloat dx = 0, GLfloat dy = 0, GLfloat dz = -1);
    virtual void setup(GLuint index, renderer* renderer);
};
#endif /* light_h */
