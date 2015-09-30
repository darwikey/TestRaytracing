#include "StdAfx.h"
#include "Cube_manager.h"



Cube_manager::Cube_manager()
{
	struct_cube _cube;

/*	_cube.position = vec3(0, 0, 0);
	_cube.size = vec3(0.2f, 0.2f, 1.f);
	m_list_cube.push_back(_cube);

	_cube.position = vec3(0, -1, 0);
	_cube.size = vec3(0.2f, 0.2f, 1.f);
	m_list_cube.push_back(_cube);

	_cube.position = vec3(-1.5f, -1.5f, 1.f);
	_cube.size = vec3(6, 3, 1);
	m_list_cube.push_back(_cube);*/

	/*_cube.size = vec3(0.2f, 0.2f, 0.2f);

	for (float x=0; x<1; x++)
	{
		for (float y=0; y<10; y++)
		{
			for (float z=0; z<10; z++)
			{
				_cube.position = vec3(x/3.f, y/3.f-2.f, z/3.f-1.f);
				m_list_cube.push_back(_cube);
			}
		}
	}*/

	_cube.position = vec3(0, 0, 0);
	_cube.size = vec3(1.5f, 1.5f, 1.5f);
	m_list_cube.push_back(_cube);
	
	fractalize(fractalize(fractalize(fractalize(m_list_cube, 1), 2), 3), 4); 


	find_list_face();	
}


list<struct_cube> Cube_manager::fractalize(list<struct_cube> fList_cube, int fIteration)
{
	list<struct_cube> _list_cube;

	for (auto it=fList_cube.begin(); it!=fList_cube.end(); ++it)
	{
		tvec3 _vertex[8];
		_vertex[0] = _vertex[1] = _vertex[2] = _vertex[3] = _vertex[4] = _vertex[5] = _vertex[6] = it->position - vec3(it->size.x * 0.5f, it->size.y * 0.5f, it->size.z * 0.5f);

		_vertex[1].x += it->size.x;
		_vertex[2].y += it->size.y;
		_vertex[3].z += it->size.z;

		_vertex[4].x += it->size.x;
		_vertex[4].y += it->size.y;
		_vertex[5].x += it->size.x;
		_vertex[5].z += it->size.z;
		_vertex[6].y += it->size.y;
		_vertex[6].z += it->size.z;

		_vertex[7] = it->position + vec3(it->size.x * 0.5f, it->size.y * 0.5f, it->size.z * 0.5f);

		for (int i=0; i<8; i++)
		{
			struct_cube _cube = push_cube(_vertex[i], 1.5f / (pow(2.f, fIteration)));
			_list_cube.push_back(_cube);
		}
	}

	return _list_cube;		
}


struct_cube Cube_manager::push_cube(tvec3 fPosition, float fSize)
{
	struct_cube _cube;
	_cube.position = fPosition;
	_cube.size = vec3(fSize, fSize, fSize);

	m_list_cube.push_back(_cube);

	return _cube;
}


void Cube_manager::find_list_face()
{

	for (auto it=m_list_cube.begin(); it!=m_list_cube.end(); ++it)
	{
		tvec3 _vertex[8];
		_vertex[0] = _vertex[1] = _vertex[2] = _vertex[3] = _vertex[4] = _vertex[5] = _vertex[6] = it->position - vec3(it->size.x * 0.5f, it->size.y * 0.5f, it->size.z * 0.5f);

		_vertex[1].x += it->size.x;
		_vertex[2].y += it->size.y;
		_vertex[3].z += it->size.z;

		_vertex[4].x += it->size.x;
		_vertex[4].y += it->size.y;
		_vertex[5].x += it->size.x;
		_vertex[5].z += it->size.z;
		_vertex[6].y += it->size.y;
		_vertex[6].z += it->size.z;

		_vertex[7] = it->position + vec3(it->size.x * 0.5f, it->size.y * 0.5f, it->size.z * 0.5f);

		struct_square _face;

		_face.vertex[0] = _vertex[0];
		_face.vertex[1] = _vertex[1];
		_face.vertex[2] = _vertex[4];
		_face.vertex[3] = _vertex[2];
		m_list_face.push_back(_face);

		_face.vertex[0] = _vertex[0];
		_face.vertex[1] = _vertex[1];
		_face.vertex[2] = _vertex[5];
		_face.vertex[3] = _vertex[3];
		m_list_face.push_back(_face);

		_face.vertex[0] = _vertex[0];
		_face.vertex[1] = _vertex[3];
		_face.vertex[2] = _vertex[6];
		_face.vertex[3] = _vertex[2];
		m_list_face.push_back(_face);

		_face.vertex[0] = _vertex[2];
		_face.vertex[1] = _vertex[4];
		_face.vertex[2] = _vertex[7];
		_face.vertex[3] = _vertex[6];
		m_list_face.push_back(_face);

		_face.vertex[0] = _vertex[1];
		_face.vertex[1] = _vertex[5];
		_face.vertex[2] = _vertex[7];
		_face.vertex[3] = _vertex[4];
		m_list_face.push_back(_face);

		_face.vertex[0] = _vertex[7];
		_face.vertex[1] = _vertex[6];
		_face.vertex[2] = _vertex[3];
		_face.vertex[3] = _vertex[5];
		m_list_face.push_back(_face);
	}

}


list<struct_square>& Cube_manager::getList_face()
{
	return m_list_face;
}