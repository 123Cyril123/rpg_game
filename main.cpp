#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

#include "Player.h"
#include "Skeleton.h"
using namespace std;
using namespace sf;



int main()
{	
	RenderWindow window(VideoMode({1980,1050}), "RPG Game", Style::Default);

	Skeleton skeleton;
	Player player;
	

	skeleton.Initialize();
	player.Initialize();

	skeleton.Load();
	player.Load();

	while (window.isOpen()) 
	{	
		while (optional<Event> event = window.pollEvent())
		{
			if (event->is<Event::Closed>())
			{
				window.close();

			}
			else if (event->is<Event::KeyPressed>())
			{
				const auto* key = event->getIf<Event::KeyPressed>();

				if (key->scancode == Keyboard::Scan::Escape)
				{
					window.close();
				}
			}
		}


		skeleton.Update();
		player.Update(skeleton);
		
		window.clear(Color::Black);
		skeleton.Draw(window);
		player.Draw(window);
		
		window.display();
	}
	return 0;
}