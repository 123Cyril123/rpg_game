#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
using namespace std;
using namespace sf;

Vector2f normalizeVector(Vector2f vector) {
	float m = sqrt(vector.x * vector.x + vector.y * vector.y);

	Vector2f normalizedVector;
	normalizedVector.x = vector.x / m;
	normalizedVector.y = vector.y / m;

	return normalizedVector;
}

int main()
{	//-------------INITIALIZE-----------------------------
	ContextSettings settings;
	settings.antiAliasingLevel = 8;
	RenderWindow window(VideoMode({1980,1050}), "RPG Game", Style::Default, State::Windowed, settings);

	vector<RectangleShape>bullets;
	
	float bulletSpeed = 4;

	


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
		skeletonSprite.setPosition({ 1800,100 });

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
		playerSprite.setPosition({ 1700, 800 });
	}
	else {
		cout << "Image failed to load" << endl;
	}

	//-------------PLAYER-----------------------------


	//bullet.setPosition(playerSprite.getPosition());

	//------------BULLET DIRECTION--------------------
	//Vector2f bulletDirection = skeletonSprite.getPosition() - bullet.getPosition();

	//bulletDirection = normalizeVector(bulletDirection);


	//------------BULLET DIRECTION--------------------
	

	//-------------INITIALIZE-----------------------------
		

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
	/*	bullet.setPosition(bullet.getPosition() + bulletDirection * bulletSpeed);*/

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
		if (Mouse::isButtonPressed(Mouse::Button::Left))
		{	
			RectangleShape bullet({ 10,5 });
			bullets.push_back(bullet);
			bullets[bullets.size() - 1].setPosition(playerSprite.getPosition());
		}
		for (size_t i = 0; i < bullets.size(); i++)
		{
			Vector2f bulletDirection;
			bulletDirection = skeletonSprite.getPosition() - bullets[i].getPosition();
			bulletDirection = normalizeVector(bulletDirection);
			bullets[i].setPosition(bullets[i].getPosition() + bulletDirection * bulletSpeed);
		}
		//----------UPDATE--------------------------------

		//----------DRAW----------------------------------
		window.clear(Color::Black);
		window.draw(skeletonSprite);
		window.draw(playerSprite);
		for (size_t i = 0; i < bullets.size(); i++)
		{
			window.draw(bullets[i]);
		}
		window.display();
		//----------DRAW----------------------------------

	}
	return 0;
}