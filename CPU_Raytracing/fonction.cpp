#include "stdAfx.h"
#include "fonction.h"







float distance2D(const tvec2& a, const tvec2& b)
{
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y));
}


float distance3D(const tvec3& a, const tvec3& b)
{
    return sqrt((a.x-b.x)*(a.x-b.x) + (a.y-b.y)*(a.y-b.y) + (a.z-b.z)*(a.z-b.z));
}

float length(const tvec3 a)
{
    return sqrt(a.x*a.x + a.y*a.y + a.z*a.z);
}

// Angle en radian
tvec2 rotate(tvec2 fCenter, tvec2 fPoint, float fAngle)
{
	tvec2 _point;

	//L'angle est orienté dans le sens trigo
	fAngle = -fAngle;

	_point.x = cos(fAngle)*(fPoint.x-fCenter.x) - sin(fAngle)*(fPoint.y-fCenter.y) + fCenter.x;
	_point.y = sin(fAngle)*(fPoint.x-fCenter.x) + cos(fAngle)*(fPoint.y-fCenter.y) + fCenter.y;

	return _point;
}


float deg_to_rad(float d)
{
	return d*0.0174533f;
}


float rad_to_deg(float r)
{
	return r*57.29578f;
}


float normalize_angle(float fAngle)
{
	if (fAngle < 0)
	{
		fAngle+=360.f;
	}

	if (fAngle >= 360.f)
	{
		fAngle -= 360.f;
	}

	return fAngle;
}


float random (float fMin, float fMax)
{
	float interval = fMax - fMin;
	return fMin + interval * rand()/(float)RAND_MAX;
}


// Profuit Scalaire
float dotProduct(const tvec2 &vec1, const tvec2 &vec2)
{
    return vec1.x*vec2.x + vec1.y*vec2.y;
}

float dotProduct(const tvec3 &vec1, const tvec3 &vec2)
{
    return vec1.x*vec2.x + vec1.y*vec2.y + vec1.z*vec2.z;
}


// Produit Vectoriel
tvec3 crossProduct(const tvec3 &vec1, const tvec3 &vec2)
{
    return vec3(vec1.y*vec2.z - vec1.z*vec2.y, 
				vec1.z*vec2.x - vec1.x*vec2.z, 
				vec1.x*vec2.y - vec1.y*vec2.x);
}


// determinant
float determinant(const tvec2& fVectorAB, const tvec2& fVectorAP)
{
	// Règle du Gamma
	return fVectorAB.x*fVectorAP.y - fVectorAB.y*fVectorAP.x;
}



tvec2 vec2(float x, float y)
{
	tvec2 a;
	a.x = x;
	a.y = y;
	return a;
}

tvec2 vec2(int x, int y)
{
	tvec2 a;
	a.x = (float)x;
	a.y = (float)y;
	return a;
}

tvec3 vec3(float x, float y, float z)
{
	tvec3 a;
	a.x = x;
	a.y = y;
	a.z = z;
	return a;
}

tvec3 vec3(int x, int y, int z)
{
	tvec3 a;
	a.x = (float)x;
	a.y = (float)y;
	a.z = (float)z;
	return a;
}

coord make_coord(int x, int y)
{
	coord a;
	a.x = x;
	a.y = y;
	return a;
}


tvec3 operator+ (tvec3 a, tvec3 b)
{
	tvec3 r;
	r.x = a.x + b.x;
	r.y = a.y + b.y;
	r.z = a.z + b.z;
	return r;
}

tvec3 operator- (tvec3 a, tvec3 b)
{
	tvec3 r;
	r.x = a.x - b.x;
	r.y = a.y - b.y;
	r.z = a.z - b.z;
	return r;
}

tvec3 operator* (tvec3 a, float b)
{
	tvec3 r;
	r.x = a.x * b;
	r.y = a.y * b;
	r.z = a.z * b;
	return r;
}

tvec3 operator* ( float b, tvec3 a)
{
	tvec3 r;
	r.x = a.x * b;
	r.y = a.y * b;
	r.z = a.z * b;
	return r;
}