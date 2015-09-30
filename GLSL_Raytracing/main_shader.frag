uniform vec2 resolution;
uniform vec3 position_camera;
uniform vec3 direction_camera;


//-------------------------------------------
// Defines
//-------------------------------------------
#define NB_SPHERE 1


//-------------------------------------------
// Structures et tableaux
//-------------------------------------------
struct ray
{
	vec3 point;
	vec3 dir;
};

struct sphere
{
	vec3 center;
	float radius;
	vec3 color;
};

struct impact
{
	bool is_impact;
	vec3 point;
	vec3 color;
};


sphere tab_sphere [NB_SPHERE];



//-------------------------------------------
// Fonctions
//-------------------------------------------
float phong_illumination(ray fRay, vec3 fNormal)
{
	float _illumination = 0.2;
	
	vec3 _light_dir = vec3(1.414, 0.0, 1.414);

	// Diffuse
	_illumination += dot(fNormal, -_light_dir) * 1.0;
	
	// Specularité
	_illumination += pow(max(dot(2 * fNormal + _light_dir, -fRay.dir), 0.0), 3.0) * 1.5;
	
	return _illumination;
}


bool simple_intersect_ray_sphere(ray fRay)
{
	// On parcourt les sphères
	for (int i = 0; i < NB_SPHERE; i++)
	{
		float b = dot(fRay.dir, fRay.point - tab_sphere[i].center);
		
		float _delta = pow(b, 2.0) - dot(fRay.point - tab_sphere[i].center, fRay.point - tab_sphere[i].center) + tab_sphere[i].radius * tab_sphere[i].radius ;
		
		if (_delta > 0.0)
		{
			if (-b + sqrt(_delta) > 0.01)
			{
				return true;
			}
		
		}
	}
	
	return false;
	
}


impact intersect_ray_sphere(ray fRay)
{
	impact _impact;
	_impact.is_impact = false;
	
	float _nearest_t = 9999999.0;
	
	// On parcourt les sphères
	for (int i = 0; i < NB_SPHERE; i++)
	{
		float b = dot(fRay.dir, fRay.point - tab_sphere[i].center);
		
		float _delta = pow(b, 2.0) - dot(fRay.point - tab_sphere[i].center, fRay.point - tab_sphere[i].center) + tab_sphere[i].radius * tab_sphere[i].radius ;
		
		if (_delta > 0.0)
		{
			float t = -b - sqrt(_delta);
			if (t < 0.01)
			{
				t = -t + sqrt(_delta);
			}
			if (t > 0.01 && t < _nearest_t)
			{
				_nearest_t = t;
			
				_impact.is_impact = true;
				_impact.point = fRay.point + t * fRay.dir;
				_impact.color = tab_sphere[i].color * phong_illumination(fRay, normalize(_impact.point - tab_sphere[i].center));
			}
		
		}
	}
	
	return _impact;
}



//-------------------------------------------
// Main
//-------------------------------------------
void main()
{
	// Camera
	vec2 uv = gl_FragCoord.xy / resolution.x;
	
	vec3 _axisX = cross(direction_camera, vec3(0.0, 1.0, 0.0));
	vec3 _axisY = cross(direction_camera, _axisX);
	
	ray _ray_camera;
	_ray_camera.point = position_camera;
	_ray_camera.dir = normalize(direction_camera + (uv.x - 0.5) * _axisX + (uv.y - 0.5 * (resolution.y / resolution.x)) * _axisY);
	
	
	// Spheres
	tab_sphere[0].center = vec3(3.0, 1.0, 0.0);
	tab_sphere[0].radius = 0.5;
	tab_sphere[0].color = vec3(1.0, 0.7, 0.2);
	
	
	vec4 _color = vec4(0.2, 0.2, 0.2, 1.0);
	
	// Test collision avec les objets
	impact _impact = intersect_ray_sphere(_ray_camera);
	
	if (_impact.is_impact)
	{
		_color.rgb = _impact.color;
	}

	
	gl_FragColor = _color;
	
}