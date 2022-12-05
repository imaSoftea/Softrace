#pragma once
#include <iostream>

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
