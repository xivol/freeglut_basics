#include "math.h"

GLfloat vec3D::length()
{
	return sqrt(x * x + y * y + z * z);
}

vec3D vec3D::normalized()
{
	GLfloat l = length();
	vec3D result = { x / l, y / l, z / l, 1.0 };
	return result;
}

vec3D vec3D::cross(const vec3D& other)
{

	vec3D result = { y * other.z - z * other.y,
					 z * other.x - x * other.z,
					 x * other.y - y * other.x };
	return result;
}

vec3D vec3D::operator-()
{
	vec3D result = { -x, -y, -z, w };
	return result;
}

vec3D vec3D::operator-(const vec3D& other)
{
	vec3D result = { x, y, z, w };
	return result -= other;
}

vec3D vec3D::operator+(const vec3D& other)
{
	vec3D result = { x, y, z, w };
	return result += other;
}

vec3D& vec3D::operator-=(const vec3D& other)
{
	x -= other.x;
	y -= other.y;
	z -= other.z;
	return *this;
}

vec3D& vec3D::operator+=(const vec3D& other)
{
	x += other.x;
	y += other.y;
	z += other.z;
	return *this;
}

vec3D matrix::operator*(const vec3D& other)
{
	vec3D result;
	for (int i = 0; i < 4; ++i)
	{
		result[i] = 0;
		for (int j = 0; j < 4; ++j)
			result[i] += values[i * 4 + j] * other.values[j];
	}
	return result;
}
