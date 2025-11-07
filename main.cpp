#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>

#include "Player.h"
#include "Skeleton.h"
#include "FrameRate.h"
#include "map.h"
using namespace std;
using namespace sf;



int main()
{	
	RenderWindow window(VideoMode({ 1980,1050 }), "RPG Game", Style::Default);
	window.setFramerateLimit(144);
	window.setVerticalSyncEnabled(true);


	map map;
	Skeleton skeleton;
	Player player;
	FrameRate framerate;
	

	skeleton.Initialize();
	player.Initialize();
	framerate.Initialize();


	map.Load();
	skeleton.Load();
	player.Load();
	framerate.Load();
	Clock clock;
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
		Time deltaTimeTimer = clock.restart();
		float deltaTime = (float)deltaTimeTimer.asMilliseconds();
		Vector2f mousePosition = Vector2f(Mouse::getPosition(window));

		framerate.Update(deltaTime,skeleton);
		skeleton.Update();
		player.Update(deltaTime, skeleton, mousePosition);
		
		window.clear(Color::Black);

		map.Draw(window);
		skeleton.Draw(window);
		player.Draw(window);
		framerate.Draw(window);
		
		window.display();

	}
	return 0;
}