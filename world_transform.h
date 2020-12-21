#pragma once
#ifndef world_transform_h
#define world_transform_h
#include "renderer.h"

class world_transform: public render_param {  };

class point : public world_transform
{
protected:
    vec3D _position = { 0,0,0,1 };
public:
    point() {}
    point(GLfloat x, GLfloat y, GLfloat z);

    inline vec3D get_position() const { return _position; }
    virtual void set_position(GLfloat x, GLfloat y, GLfloat z);
    virtual void set_position(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    virtual void translate_by(GLfloat x, GLfloat y, GLfloat z);

    virtual void setup(renderer* renderer);
};

class oriented : public world_transform
{
protected:
    vec3D _rotation = { 0,0,0,1 };
public:
    inline vec3D get_rotation() { return _rotation; }
    virtual void set_rotation(GLfloat x, GLfloat y, GLfloat z);
    virtual void set_rotation(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    virtual void rotate_by(GLfloat x, GLfloat y, GLfloat z);
    
    virtual void setup(renderer* renderer);
};

class extended : public world_transform
{
protected:
    vec3D _scale = { 1,1,1,1 };
public:
    inline vec3D get_scale() { return _scale; }
    virtual void set_scale(GLfloat x, GLfloat y, GLfloat z);
    virtual void set_scale(GLfloat x, GLfloat y, GLfloat z, GLfloat w);
    virtual void scale_by(GLfloat x, GLfloat y, GLfloat z);

    virtual void setup(renderer* renderer);
};

class directional : public point, public oriented
{
protected:
    vec3D _direction = { 0,0,-1,1 };
    vec3D _target = { 0,0,-1,1 };

    void reset_direction();
public:
    directional(GLfloat x, GLfloat y, GLfloat z, GLfloat targetx, GLfloat targety, GLfloat targetz);
 
    virtual void set_position(GLfloat x, GLfloat y, GLfloat z);

    inline vec3D get_target() { return _target; }
    virtual void set_target(GLfloat x, GLfloat y, GLfloat z, GLfloat w = 1);
    virtual void translate_target_by(GLfloat x, GLfloat y, GLfloat z);
    
    virtual vec3D get_direction();
    virtual void set_rotation(GLfloat x, GLfloat y, GLfloat z);

    //virtual void setup(renderer* renderer);
};

#endif /* world_transform_h */

