#pragma once



class Cube_manager : public Singleton<Cube_manager> 
{
//---------------------------------------------------------------------------------------------
public:
//---------------------------------------------------------------------------------------------
	Cube_manager(void);
	~Cube_manager(void);

	list<struct_cube> fractalize(list<struct_cube> fList_cube, int fIteration);
	struct_cube push_cube(tvec3 fPosition, float fSize);

	void find_list_face();

	list<struct_square>& getList_face();


//---------------------------------------------------------------------------------------------
private:
//---------------------------------------------------------------------------------------------
	list<struct_cube> m_list_cube;
	list<struct_square> m_list_face;
};

