// Raytracing.cpp : définit le point d'entrée pour l'application console.
//

#include "stdafx.h"
#include "Display.h"


int _tmain(int argc, _TCHAR* argv[])
{

	Display* _screen = Display::getInstance();

	bool Running = true;

	while (Running)
	{
        //**********************************************
        // Clavier et souris
        //**********************************************
        Event event;
        while (_screen->m_screen.GetEvent(event))
        {
            switch (event.Type)
            {
                // exit if the window is closed
            case Event::Closed:
                Running = false;
                break;

            case Event::MouseMoved :
                //cursor.x = (float)event.MouseMove.X;
                //cursor.y = (float)event.MouseMove.Y;
                break;

			default:
				break;

            }
        }

		Display::getInstance()->draw_face();

		Display::getInstance()->display_render();

		_screen->m_screen.Display();
	}

	return 0;
}

