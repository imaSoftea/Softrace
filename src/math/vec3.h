#pragma once
#include <iostream>
#include <cstdlib>

const float infinity = std::numeric_limits<float>::infinity();
const float pi = 3.1415926f;

class vec3
{
public:

	/*_________ Variables & Definitions _________*/
	float val[3];

	/*_________ Operators _________*/

	/* Vec3 Operators */
	vec3& operator+= (const vec3& v);
	vec3& operator-= (const vec3& v);
	vec3& operator*= (const vec3& v);
	vec3& operator/= (const vec3& v);

	/* Float Operators */
	vec3& operator+= (const float f);
	vec3& operator-= (const float f);
	vec3& operator*= (const float f);
	vec3& operator/= (const float f);

	/*_________ Functions _________*/
	float dotProd(const vec3 v) const;
	vec3 crossProd(const vec3 v) const;
	vec3 unitVec() const;
	float length() const;
	float lengthSquared() const;
	bool near_zero() const;

	static vec3 random();
	static vec3 random(float min, float max);
	static vec3 random_unit_vector();
	static vec3 random_in_unit_sphere();
	static vec3 random_in_hemisphere(const vec3& normal);
	static vec3 reflect(const vec3& v, const vec3& n);
	static vec3 refract(const vec3& uv, const vec3& n, float etai_over_etat);
	static vec3 random_in_unit_disk();

	/*_________ Constructors _________*/
	vec3() : val{ 0, 0, 0 } {}
	vec3(float v1, float v2, float v3) : val{v1, v2, v3} {}

};

// Alt Names
using point3 = vec3;
using color = vec3;

// Contains all Utillity Functions not Contained in the class...

/*_________ Operators _________*/

// Vec3 Operators
inline std::ostream& operator<<(std::ostream& o, const vec3& v) {
	return o << v.val[0] << ' ' << v.val[1] << ' ' << v.val[2];
}

inline vec3 operator+ (const vec3 v, const vec3 w) {
	return vec3(v.val[0] + w.val[0], v.val[1] + w.val[1], v.val[2] + w.val[2]);
}

inline vec3 operator-(const vec3& v, const vec3& w) {
	return vec3(v.val[0] - w.val[0], v.val[1] - w.val[1], v.val[2] - w.val[2]);
}

inline vec3 operator*(const vec3& v, const vec3& w) {
	return vec3(v.val[0] * w.val[0], v.val[1] * w.val[1], v.val[2] * w.val[2]);
}

// Float Operators
inline vec3 operator*(const vec3& v, const float f) {
	return vec3(v.val[0] * f, v.val[1] * f, v.val[2] * f);
}
inline vec3 operator*(const float f, const vec3& v) {
	return vec3(v.val[0] * f, v.val[1] * f, v.val[2] * f);
}

inline vec3 operator/(const vec3& v, const float f) {
	return vec3(v.val[0] / f, v.val[1] / f, v.val[2] / f);
}
inline vec3 operator/(const float f, const vec3& v) {
	return vec3(v.val[0] / f, v.val[1] / f, v.val[2] / f);
}

inline float random_float() {
	// Returns a random real in [0,1).
	return rand() / (RAND_MAX + 1.0f);
}

inline float random_float(float min, float max) {
	// Returns a random real in [min,max).
	return min + (max - min) * random_float();
}

inline float clamp(float x, float min, float max) {
	if (x < min) return min;
	if (x > max) return max;
	return x;
}

// Contains all Class Functions & Overloads for "vec3"

/*_________ Operators _________*/

// Vec3 Operators
inline vec3& vec3::operator+= (const vec3& v){
	val[0] += v.val[0];
	val[1] += v.val[1];
	val[2] += v.val[2];
	return *this;
}
inline vec3& vec3::operator-= (const vec3& v){
	val[0] -= v.val[0];
	val[1] -= v.val[1];
	val[2] -= v.val[2];
	return *this;
}
inline vec3& vec3::operator*= (const vec3& v){
	val[0] *= v.val[0];
	val[1] *= v.val[1];
	val[2] *= v.val[2];
	return *this;
}
inline vec3& vec3::operator/= (const vec3& v){
	val[0] /= v.val[0];
	val[1] /= v.val[1];
	val[2] /= v.val[2];
	return *this;
}

// Float Operators
inline vec3& vec3::operator+= (const float f){
	val[0] += f;
	val[1] += f;
	val[2] += f;
	return *this;
}
inline vec3& vec3::operator-= (const float f){
	val[0] -= f;
	val[1] -= f;
	val[2] -= f;
	return *this;
}
inline vec3& vec3::operator*= (const float f){
	val[0] *= f;
	val[1] *= f;
	val[2] *= f;
	return *this;
}
inline vec3& vec3::operator/= (const float f){
	val[0] /= f;
	val[1] /= f;
	val[2] /= f;
	return *this;
}

/*_________ Functions _________*/

// Dot Product
inline float vec3::dotProd(const vec3 v) const
{
	return val[0] * v.val[0] + val[1] * v.val[1] + val[2] * v.val[2];
}

// Cross Product
inline vec3 vec3::crossProd(const vec3 v) const
{
	return vec3
	(
		val[1] * v.val[2] - val[2] * v.val[1],
		val[2] * v.val[0] - val[0] * v.val[2],
		val[0] * v.val[1] - val[1] * v.val[0]
	);
}

// Gets Length
inline float vec3::length() const
{
	return sqrt(val[0] * val[0] + val[1] * val[1] + val[2] * val[2]);
}

// Returns a Unit Vector
inline vec3 vec3::unitVec() const
{
	float x = length();
	vec3 temp(val[0] / x, val[1] / x, val[2] / x);
	return temp;
}

// Gets Length^2
inline float vec3::lengthSquared() const
{
	return val[0] * val[0] + val[1] * val[1] + val[2] * val[2];
}

// Creates a random unit vec3
inline vec3 vec3::random() {
	return vec3(random_float(), random_float(), random_float());
}

// Random vec3 with range
inline vec3 vec3::random(float min, float max) {
	return vec3(random_float(min, max), random_float(min, max), random_float(min, max));
}

// Random vec3 in a sphere
inline vec3 vec3::random_in_unit_sphere() {
	while (true) {
		auto p = random(-1, 1);
		if (p.lengthSquared() >= 1) continue;
		return p;
	}
}

// Random vec3 is hemisphere
inline vec3 vec3::random_in_hemisphere(const vec3& normal)
{
	vec3 in_unit_sphere = random_in_unit_sphere();
	if (in_unit_sphere.dotProd(normal) > 0.0f) // In the same hemisphere as the normal
		return in_unit_sphere;
	else
		return -1 * in_unit_sphere;
}

// Checks if near zero
inline bool vec3::near_zero() const
{
	const auto s = 1e-8f;
	return (fabs(val[0]) < s) && (fabs(val[1]) < s) && (fabs(val[2]) < s);
}

// Reflects a vec3
inline vec3 vec3::reflect(const vec3& v, const vec3& n)
{
	return v - v.dotProd(n) * n * 2;
}

// Refracts a vec3
inline vec3 vec3::refract(const vec3& uv, const vec3& n, float etai_over_etat) {
	auto cos_theta = fmin( n.dotProd(-1 * uv), 1.0f);
	vec3 r_out_perp = etai_over_etat * (uv + cos_theta * n);
	vec3 r_out_parallel = -sqrt(fabs(1.0f - r_out_perp.lengthSquared())) * n;
	return r_out_perp + r_out_parallel;
}

// Random vec3 in a disk unit
inline vec3 vec3::random_in_unit_disk() {
	while (true) {
		auto p = vec3(random_float(-1.0f, 1.0f), random_float(-1.0f, 1.0f), 0.0f);
		if (p.lengthSquared() >= 1) continue;
		return p;
	}
}

// returns a random unit vector that fits in the sphere;
inline vec3 vec3::random_unit_vector()
{
	return random_in_unit_sphere().unitVec();
}