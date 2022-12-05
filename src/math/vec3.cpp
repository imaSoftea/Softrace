#pragma once
#include "vec3.h"

// Contains all Class Functions & Overloads for "vec3"

/*_________ Operators _________*/

// Vec3 Operators
vec3& vec3::operator+= (const vec3& v){
	val[0] += v.val[0];
	val[1] += v.val[1];
	val[2] += v.val[2];
	return *this;
}
vec3& vec3::operator-= (const vec3& v){
	val[0] -= v.val[0];
	val[1] -= v.val[1];
	val[2] -= v.val[2];
	return *this;
}
vec3& vec3::operator*= (const vec3& v){
	val[0] *= v.val[0];
	val[1] *= v.val[1];
	val[2] *= v.val[2];
	return *this;
}
vec3& vec3::operator/= (const vec3& v){
	val[0] /= v.val[0];
	val[1] /= v.val[1];
	val[2] /= v.val[2];
	return *this;
}

// Float Operators
vec3& vec3::operator+= (const float f){
	val[0] += f;
	val[1] += f;
	val[2] += f;
	return *this;
}
vec3& vec3::operator-= (const float f){
	val[0] -= f;
	val[1] -= f;
	val[2] -= f;
	return *this;
}
vec3& vec3::operator*= (const float f){
	val[0] *= f;
	val[1] *= f;
	val[2] *= f;
	return *this;
}
vec3& vec3::operator/= (const float f){
	val[0] /= f;
	val[1] /= f;
	val[2] /= f;
	return *this;
}

/*_________ Functions _________*/

// Dot Product
float vec3::dotProd(const vec3 v) const
{
	return val[0] * v.val[0] + val[1] * v.val[1] + val[2] * v.val[2];
}

// Cross Product
vec3 vec3::crossProd(const vec3 v) const
{
	return vec3
	(
		val[1] * v.val[2] - val[2] * v.val[1],
		val[2] * v.val[0] - val[0] * v.val[2],
		val[0] * v.val[1] - val[1] * v.val[0]
	);
}

// Gets Length
float vec3::length() const
{
	return sqrt(val[0] * val[0] + val[1] * val[1] + val[2] * val[2]);
}

// Returns a Unit Vector
vec3 vec3::unitVec() const
{
	float x = length();
	vec3 temp(val[0] / x, val[1] / x, val[2] / x);
	return temp;
}

// Gets Length^2
float vec3::lengthSquared() const
{
	return val[0] * val[0] + val[1] * val[1] + val[2] * val[2];
}
