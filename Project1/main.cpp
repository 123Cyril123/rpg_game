#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

int main()
{	//-------------INITIALIZE-----------------------------
	ContextSettings settings;
	settings.antiAliasingLevel = 8;
	RenderWindow window(VideoMode({1980,1050}), "RPG Game", Style::Default, State::Fullscreen, settings);

	

	// CIRCLE
	CircleShape circle(50.0f);
	circle.setFillColor(Color::Green);
	circle.setPosition(Vector2f{50, 400});
	circle.setOutlineThickness(5.0f);
	circle.setOutlineColor(Color::Blue);

	// RECTANGLE
	RectangleShape rectangle(Vector2f{ 200,50 });
	rectangle.setPosition(Vector2f{120,300 });
	rectangle.setFillColor(Color::Yellow);
	rectangle.setOutlineThickness(5.0f);
	rectangle.setOutlineColor(Color::Red);
	rectangle.setOrigin(rectangle.getSize() / 2.0f); // sets the origin to the center instead of the top left corner of the object 

	// SQUARE - POLYGON - TETRAGON
	CircleShape square(50.0f, 4);
	square.setPosition(Vector2f{ 50.0f,50.0f });
	square.setFillColor(Color::Cyan);
	square.setRotation(degrees(45.0f));

	// TRIANGLE - POLYGON - TRIGON
	CircleShape triangle(50.0f, 3);
	triangle.setFillColor(Color::Red);

	// OCTAGON - POLYGON
	CircleShape octagon(50.0f, 8);
	octagon.setFillColor(Color::White);
	octagon.setPosition(Vector2f{ 50.0f, 150.0f });

	CircleShape almostCircle(50.0f, 9);
	almostCircle.setFillColor(Color::Magenta);



	//-------------INITIALIZE-----------------------------
	while (window.isOpen()) 
	{	


		//----------UPDATE--------------------------------
		while (optional<Event> event = window.pollEvent())
		{
			if (event->is<Event::Closed>())
			{
				window.close();

			}
			else if (event->is<Event::KeyPressed>())
			{
				window.close();
			}
		}
		//----------UPDATE--------------------------------

		//----------DRAW----------------------------------
		window.clear(Color::Black);
		window.draw(circle);
		window.draw(rectangle);
		window.draw(square);
		window.draw(triangle); 
		window.draw(octagon);
		window.draw(almostCircle);
		window.display();
		//----------DRAW----------------------------------

	}
	return 0;
}