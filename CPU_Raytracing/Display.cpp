#include "StdAfx.h"
#include "Display.h"
#include "Cube_manager.h"
#include "Lamp_manager.h"


Display::Display() 
{
	m_width_screen = 800;
	m_height_screen = 500;
	m_current_pixel = make_coord(0, 0);

	//Camera
	m_camera0 = vec3(-6, 0, 0);
	m_angle_camera = vec2(0.f, 0.f);

	// Image de rendu
	m_img_render.Create(m_width_screen, m_height_screen, Color(0,0,0));
	m_sprite_render.SetImage(m_img_render);
	m_sprite_render.SetPosition(0,0);

	// Creation nouvelle fenetre
    m_screen.Create(VideoMode((int)m_width_screen, (int)m_height_screen, 32), "Ray tracing");

}




void Display::draw_face()
{
	Clock _clock;
	_clock.Reset();

	for (m_current_pixel.x ; m_current_pixel.x<m_width_screen; m_current_pixel.x++)
	{
		for (m_current_pixel.y = 0; m_current_pixel.y<m_height_screen; m_current_pixel.y++)
		{

			draw_pixel(m_current_pixel.x, m_current_pixel.y);
			
			if (_clock.GetElapsedTime() >= 1.5f)
			{
				return;
			}
						
			if (m_current_pixel.x >= m_width_screen-1 && m_current_pixel.y >= m_height_screen-1)
			{
				m_current_pixel.x = 0;
				m_current_pixel.y = 0;
				return;
			}
		}
	}

	m_current_pixel.x = 0;
	m_current_pixel.y = 0;

}


void Display::draw_pixel(int x, int y)
{
	list<struct_square>& _list_face = Cube_manager::getInstance()->getList_face();


	bool _collision = 0;
	tvec3 _nearest_point = vec3(9999999999.f,0.f,0.f);

	tvec3 _camera1 = m_camera0 + vec3(1.f, (float)x/(float)m_width_screen -0.5f, (float)y / (float)m_height_screen -0.5f);
	
	/*tvec2 _p = rotate(vec2(m_camera0.y, m_camera0.z), vec2(_camera1.y, _camera1.z), m_angle_camera.y);
	_camera1.y = _p.x;
	_camera1.z = _p.y;

	_p = rotate(vec2(m_camera0.x, m_camera0.y), vec2(_camera1.x, _camera1.y), m_angle_camera.x);
	_camera1.x = _p.x;
	_camera1.y = _p.y;*/
	
	tvec3 _radius = _camera1  - m_camera0;


	for (auto it=_list_face.begin(); it!=_list_face.end(); ++it)
	{
		tvec3 _AO = m_camera0 - it->vertex[0];
		tvec3 _normal = crossProduct(it->vertex[1]-it->vertex[0], it->vertex[3]-it->vertex[0]);
		float _k = dotProduct(_normal, _radius);

		tvec3 I;
		//I.z = - dotProduct(_normal, _AO) / _k;
		I.x = dotProduct(crossProduct(_AO, it->vertex[3]-it->vertex[0]), _radius) / _k;
		I.y = dotProduct(crossProduct(it->vertex[1]-it->vertex[0], _AO), _radius) / _k;
			
		//if (I.z >= 0.f && I.x >= 0.f && I.x <= 1.f && I.y >= 0.f && I.y <= 1.f)
		if (I.x >= 0.f&& I.y >= 0.f && I.x <= 1.f  && I.y <= 1.f)
		{
			tvec3 _point_face = it->vertex[0] + I.x * (it->vertex[1]-it->vertex[0]) + I.y * (it->vertex[3]-it->vertex[0]);

			if (distance3D(m_camera0, _point_face) < distance3D(m_camera0, _nearest_point))
			{
				_nearest_point = _point_face;
			}

			_collision = 1;
		}
	}

	if (_collision)
	{
				
		int _illumination = (int) Lamp_manager::getInstance()->find_illumination(_nearest_point);
		_illumination = min(_illumination, 255);

		m_img_render.SetPixel(x, y, Color(_illumination ,_illumination,_illumination));
	}
	else
	{
		m_img_render.SetPixel(x, y, Color(0,0,255));
	}

}



void Display::display_render()
{
	m_screen.Draw(m_sprite_render);
}