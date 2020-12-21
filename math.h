#pragma once
#ifndef math_h
#define math_h
#include "GL/freeglut.h"
#include <cmath>

union vec3D
{
    GLfloat values[4];
    struct
    {
        GLfloat x;
        GLfloat y;
        GLfloat z;
        GLfloat w;
    };

    GLfloat length();
    vec3D normalized();
    vec3D cross(const vec3D& other);

    vec3D operator-();
    vec3D operator-(const vec3D& other);
    vec3D operator+(const vec3D& other);
    vec3D& operator-=(const vec3D& other);
    vec3D& operator+=(const vec3D& other);

    inline operator GLfloat* const () { return values; }
};

struct matrix {
    GLfloat values[16];

    vec3D operator*(const vec3D& other);
    inline GLfloat* operator[] (int i) { return &values[i * 4]; }
    inline operator GLfloat* () { return values; }
};

union tex2D
{
    GLfloat values[3];
    struct
    {
        GLfloat u;
        GLfloat v;
        GLfloat w;
    };

    inline operator GLfloat* () { return values; }
};

#endif /*math_h */