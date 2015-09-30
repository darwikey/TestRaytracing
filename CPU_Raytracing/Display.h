#pragma once




class Display : public Singleton<Display>
{
//---------------------------------------------------------------------------------------------
public:
//---------------------------------------------------------------------------------------------
	Display();


	void draw_face();
	void draw_pixel(int x, int y);
	void display_render();


	sf::RenderWindow m_screen;
//---------------------------------------------------------------------------------------------
private:
//---------------------------------------------------------------------------------------------
	Image m_img_render;
	Sprite m_sprite_render;

	tvec3 m_camera0;
	tvec3 m_camera1;
	tvec2 m_angle_camera;

	int m_width_screen;
	int m_height_screen;

	coord m_current_pixel;
};

