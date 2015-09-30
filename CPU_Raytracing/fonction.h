#pragma once


using namespace sf;
using namespace std;



//---------------------------------------------------------------------------------------------
// STRUCTURES
//---------------------------------------------------------------------------------------------

typedef struct
{
	float x;
	float y;
} tvec2;


typedef struct
{
	float x;
	float y;
	float z;
} tvec3;


typedef struct
{
	int x;
	int y;
} coord;


typedef struct
{
	tvec3 vertex[4];
} struct_square;


typedef struct
{
	tvec3 position;
	tvec3 size;
} struct_cube;


typedef struct
{
	tvec3 position;
	float intensity;
} struct_lamp;


//---------------------------------------------------------------------------------------------
// FONCTIONS
//---------------------------------------------------------------------------------------------

float distance2D(const tvec2& a, const tvec2& b);
float distance3D(const tvec3& a, const tvec3& b);
float length(const tvec3 a);


tvec2 rotate(tvec2 fCenter, tvec2 fPoint, float fAngle);
float deg_to_rad(float d);
float rad_to_deg(float r);
float normalize_angle(float fAngle);


float random (float fMin, float fMax);


float dotProduct(const tvec2 &vec1, const tvec2 &vec2);
float dotProduct(const tvec3 &vec1, const tvec3 &vec2);
tvec3 crossProduct(const tvec3 &vec1, const tvec3 &vec2);
float determinant(const tvec2& fVectorAB, const tvec2& fVectorAP);


tvec2 vec2(float x, float y);
tvec2 vec2(int x, int y);
tvec3 vec3(float x, float y, float z);
tvec3 vec3(int x, int y, int z);
coord make_coord(int x, int y);

tvec3 operator+ (tvec3, tvec3);
tvec3 operator- (tvec3, tvec3);
tvec3 operator* (tvec3, float);
tvec3 operator* (float, tvec3);
