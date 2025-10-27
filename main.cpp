#include <SFML/Graphics.hpp>
#include <iostream>
using namespace std;
using namespace sf;

int main()
{	//-------------INITIALIZE-----------------------------
	ContextSettings settings;
	settings.antiAliasingLevel = 8;
	RenderWindow window(VideoMode({1980,1050}), "RPG Game", Style::Default, State::Windowed, settings);

	//-------------INITIALIZE-----------------------------

	//-------------SKELETON-----------------------------
	
	Texture skeletonTexture;
	Sprite skeletonSprite(skeletonTexture);

	if (skeletonTexture.loadFromFile("Project1/assets/enemy/textures/spriteSheet.png"))
	{
		int XIndex = 0;
		int YIndex = 2;

		skeletonSprite.setTexture(skeletonTexture);
		skeletonSprite.setTextureRect(IntRect({ XIndex * 64, YIndex * 64 }, { 64,64 }));
		skeletonSprite.scale({ 2,2 });
		skeletonSprite.setPosition({ 400,100 });

	}

	//-------------SKELETON-----------------------------
	
	
	//-------------PLAYER-----------------------------
	Texture playerTexture;
	Sprite playerSprite(playerTexture);
	

	if (playerTexture.loadFromFile("Project1/assets/player/textures/characters.png"))
	{	
		int XIndex = 0;
		int YIndex = 0;

		playerSprite.setTexture(playerTexture);
		playerSprite.setTextureRect(IntRect({XIndex*32, YIndex*32}, {32,32}));
		playerSprite.scale({ 4,4 });
	}
	else {
		cout << "Image failed to load" << endl;
	}

	//-------------PLAYER-----------------------------

	


	//-------------LOAD-----------------------------
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
				const auto* key = event->getIf<Event::KeyPressed>();

				if (key->scancode == Keyboard::Scan::Escape)
				{
					window.close();
				}
			}
		}
		Vector2f playerPosition = playerSprite.getPosition();
		int speed = 4;
		if (Keyboard::isKeyPressed(Keyboard::Scan::W))
		{	
			playerSprite.setPosition({ playerPosition.x, playerPosition.y - speed });
		}
		if (Keyboard::isKeyPressed(Keyboard::Scan::A))
		{	
			playerSprite.setPosition({ playerPosition.x - speed, playerPosition.y });
		}
		if (Keyboard::isKeyPressed(Keyboard::Scan::S))
		{	
			playerSprite.setPosition({ playerPosition.x, playerPosition.y + speed});
		}
		if (Keyboard::isKeyPressed(Keyboard::Scan::D))
		{	

			playerSprite.setPosition({ playerPosition.x + speed, playerPosition.y });
		}
		//----------UPDATE--------------------------------

		//----------DRAW----------------------------------
		window.clear(Color::Black);
		window.draw(skeletonSprite);
		window.draw(playerSprite);
		window.display();
		//----------DRAW----------------------------------

	}
	return 0;
}