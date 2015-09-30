#include "StdAfx.h"
#include "Lamp_manager.h"
#include "Cube_manager.h"


Lamp_manager::Lamp_manager()
{
	struct_lamp _lamp;
	_lamp.intensity = 15;
	_lamp.position = vec3(-5, 1, -3);
	m_list_lamp.push_back(_lamp);

	_lamp.position = vec3(-5, -1, -3);
	m_list_lamp.push_back(_lamp);
}



float Lamp_manager::find_illumination(tvec3 fPoint)
{
	float _illumination = 0;

	for (auto it_lamp=m_list_lamp.begin(); it_lamp!=m_list_lamp.end(); ++it_lamp)
	{
		tvec3 _position_lamp = it_lamp->position;
		list<struct_square>& _list_face = Cube_manager::getInstance()->getList_face();


		bool _collision = 0;
		float _distance_lamp_point = distance3D(_position_lamp, fPoint);

		tvec3 _radius = fPoint - it_lamp->position;

		for (auto it_face=_list_face.begin(); it_face!=_list_face.end(); ++it_face)
		{
			tvec3 _AO = it_lamp->position - it_face->vertex[0];
			tvec3 _normal = crossProduct(it_face->vertex[1]-it_face->vertex[0], it_face->vertex[3]-it_face->vertex[0]);
			float _k = dotProduct(_normal, _radius);

			tvec3 I;
			//I.z = - dotProduct(_normal, _AO) / _k;
			I.x = dotProduct(crossProduct(_AO, it_face->vertex[3]-it_face->vertex[0]), _radius) / _k;
			I.y = dotProduct(crossProduct(it_face->vertex[1]-it_face->vertex[0], _AO), _radius) / _k;
			


			//if (I.z >= 0.f && I.x >= 0.f && I.x <= 1.f && I.y >= 0.f && I.y <= 1.f)

			// S'il y a collison entre le rayon et une face
			if (I.x >= 0.f&& I.y >= 0.f && I.x <= 1.f  && I.y <= 1.f)
			{
				tvec3 _point_face = it_face->vertex[0] + I.x * (it_face->vertex[1]-it_face->vertex[0]) + I.y * (it_face->vertex[3]-it_face->vertex[0]);

				float _d = distance3D(_position_lamp, _point_face);

				// Si la longueur du rayon est plus petite que la distance lampe/point, il y a collision
				if (_d + 0.000001 < _distance_lamp_point)
				{
					_collision = 1;
					break;
				}

			}
		}
		
		if (_collision == 0)
		{

			_illumination += it_lamp->intensity / (_distance_lamp_point* _distance_lamp_point);

		}


	}

	return 100.f * _illumination;
}