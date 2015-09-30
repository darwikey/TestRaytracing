#include <SFML/Graphics.hpp>
#include <stdio.h>
#include <stdlib.h>
#include <string>      
#include <iostream>   
#include <sstream>


int main()
{
	// Create the main window
	sf::RenderWindow window(sf::VideoMode(800, 600), "Raytracing");
	//window.setVerticalSyncEnabled(true);

	sf::RenderTexture surface;
	surface.create(800, 600);


	// Shader
	if (!sf::Shader::isAvailable())
	{
		return EXIT_FAILURE;
	}

	sf::Shader main_shader;
	if (!main_shader.loadFromFile("main_shader.frag", sf::Shader::Fragment))
	{
		return EXIT_FAILURE;
	}

	// Font
	sf::Font arial;
	if (!arial.loadFromFile("arial.ttf"))
	{
		return EXIT_FAILURE;
	}


	sf::Clock clock;

	// Start the game loop
	while (window.isOpen())
	{
		// Process events
		sf::Event event;
		while (window.pollEvent(event))
		{
			// Close window : exit
			if (event.type == sf::Event::Closed)
				window.close();
		}

		// Clear screen
		window.clear();


		main_shader.setParameter("resolution", 800.f, 600.f);
		main_shader.setParameter("position_camera", sf::Vector3f(0.f, 1.f, 0.f));
		main_shader.setParameter("direction_camera", sf::Vector3f(1.f, 0.f, 0.f));


		sf::RenderStates state;
		state.shader = &main_shader;
		window.draw(sf::Sprite(surface.getTexture()), state);


		// FPS
		std::ostringstream string_fps;
		string_fps << "Fps = " << 1.f / clock.restart().asSeconds();

		sf::Text text_fps (string_fps.str(), arial, 14);
		text_fps.setPosition(5.f, 5.f);
		window.draw(text_fps);


		// Update the window
		window.display();
	}

	return EXIT_SUCCESS;
}