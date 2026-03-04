#include <SFML/Graphics.hpp>
#include <iostream>
#include <math.h>
#include <vector>
#include <string>

#include "Player.h"
#include "Skeleton.h"
#include "FrameRate.h"
#include "Math.h"
#include "map.h"
#include "Item.h"

using namespace std;
using namespace sf;

void SpawnItems(vector<Item>& items, int count)
{
	items.clear();
	for (int i = 0; i < count; i++)
	{
		Item newItem;
		float randomX = (rand() % 1780) + 100;
		float randomY = (rand() % 850) + 100;

		newItem.Initialize(Vector2f(randomX, randomY));
		items.push_back(newItem);
	}
}

void SpawnBullets(vector<Bullet>& enemyBullets, Vector2f playerPosition, float speed)
{
	int edge = rand() % 4;
	float startX, startY;

	if (edge == 0)   // nahore
	{
		startX = (rand() % 1980);
		startY = -50;
	}
	else if (edge == 1)  // prava strana
	{
		startX = 2030;
		startY = (rand() % 1050);
	}
	else if (edge == 2)  // dole
	{
		startX = (rand() % 1980);
		startY = 1100;
	}
	else {  // leva strana
		startX = -50;
		startY = (rand() & 1050);
	}
	Bullet newBullet;
	newBullet.Initialize(Vector2f{ startX, startY }, playerPosition, speed);
	enemyBullets.push_back(newBullet);
}

int main()
{	
	srand(static_cast<unsigned>(time(NULL)));

	RenderWindow window(VideoMode({ 1980,1050 }), "Hra", Style::Default);
	window.setFramerateLimit(144);
	window.setVerticalSyncEnabled(true);


	map map;
	Skeleton skeleton;
	Player player;
	FrameRate framerate;
	

	player.Initialize();
	framerate.Initialize();


	map.Load();
	player.Load();
	framerate.Load();

	int currentLevel = 1;
	int score = 0;
	int itemsCollected = 0;
	int itemsNeeded = 5;
	vector<Item> activeItems;
	float enemySpawnTimer = 0;
	float currentSpawnRate = 800.0f;
	float enemyBulletSpeed = 0.5f;
	vector<Bullet> enemyBullets;
	SpawnItems(activeItems, itemsNeeded);

	Font uiFont;
	if (!uiFont.openFromFile("Project1/assets/fonts/pala.ttf"))
	{
		cout << "User interface not loaded" << endl;
	}
	else {
		cout << "User interface font loaded" << endl;
	}

	Text uiText(uiFont);
	uiText.setCharacterSize(36);
	uiText.setFillColor(Color::White);
	uiText.setPosition({ 20.0f,20.0f });
	uiText.setOutlineColor(Color::Black);
	uiText.setOutlineThickness(2.0f);

	bool isGameOver = false;
	Text uiText2(uiFont);
	uiText2.setString("Umrel jsi, stiskni enter");
	uiText2.setCharacterSize(64);
	uiText2.setFillColor(Color::Red);
	uiText2.setOutlineColor(Color::White);
	uiText2.setOutlineThickness(4.0f);
	uiText2.setPosition({ 600.0f, 450.0f });

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
		if (!isGameOver)
		{

		
			framerate.Update(deltaTime,skeleton);
			skeleton.Update();
			player.Update(deltaTime, skeleton, mousePosition);

			enemySpawnTimer += deltaTime;
			if (enemySpawnTimer >= currentSpawnRate)
			{
				SpawnBullets(enemyBullets, player.sprite.getPosition(), enemyBulletSpeed);
				enemySpawnTimer = 0;
			}

			for (int i = 0; i < enemyBullets.size(); i++)
			{
				enemyBullets[i].Update(deltaTime);

				if (Math::checkRectCollision(player.GetHitboxBounds(), enemyBullets[i].GetGlobalBounds()))
				{
					isGameOver = true;
					break;
				}

				Vector2f pos = enemyBullets[i].GetGlobalBounds().position;
				if (pos.x < -500 || pos.x > 2500 || pos.y < -500 || pos.y > 1500)
				{
					enemyBullets.erase(enemyBullets.begin() + i);
					i--;
				}
			}

			for (auto& item : activeItems)
			{
				item.Update(deltaTime);
			}

			for (int i = 0; i < activeItems.size(); i++)
			{
				if (Math::checkRectCollision(player.GetHitboxBounds(), activeItems[i].GetGlobalBounds()))
				{
					activeItems.erase(activeItems.begin() + i);
					itemsCollected++;
					score++;
				
					break;
				}
			}

			if (itemsCollected >= itemsNeeded)
			{
				currentLevel++;
				currentSpawnRate -= 50;
				enemyBulletSpeed += 0.1f;
				itemsCollected = 0;
				itemsNeeded++;
				enemyBullets.clear();

				SpawnItems(activeItems, itemsNeeded);

				player.sprite.setPosition({ 990,525 });
			}



		}
		else {
			if (Keyboard::isKeyPressed(Keyboard::Scan::Enter))
			{
				isGameOver = false;
				currentLevel = 1;
				score = 0;
				itemsCollected = 0;
				itemsNeeded = 5;

				currentSpawnRate = 800.0f;
				enemyBulletSpeed = 0.5f;
				enemySpawnTimer = 0;

				enemyBullets.clear();
				SpawnItems(activeItems, itemsNeeded);
				player.sprite.setPosition({ 990.0f, 525.0f });

			}
		}
		uiText.setString("Level: " + to_string(currentLevel) +
			"   |   Items: " + to_string(itemsCollected) + " / " + to_string(itemsNeeded) + "   |   Score: " + to_string(score));

		window.clear(Color::Black);

		map.Draw(window);

		for (auto& item : activeItems)
		{
			item.Draw(window);
		}

		for (auto& bullet : enemyBullets)
		{
			bullet.Draw(window);
		}
		player.Draw(window);
		framerate.Draw(window);
		window.draw(uiText);

		if (isGameOver)
		{
			window.draw(uiText2);
		}

		window.display();
	}
	return 0;
}