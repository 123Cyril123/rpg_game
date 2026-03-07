#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include <iostream>
#include <math.h>
#include <vector>
#include <string>

#ifdef _DEBUG
#pragma comment(lib, "sfml-graphics-d.lib")
#pragma comment(lib, "sfml-window-d.lib")
#pragma comment(lib, "sfml-audio-d.lib")
#pragma comment(lib, "sfml-system-d.lib")
#else
#pragma comment(lib, "sfml-graphics.lib")
#pragma comment(lib, "sfml-window.lib")
#pragma comment(lib, "sfml-audio.lib")
#pragma comment(lib, "sfml-system.lib")
#endif

#include "Player.h"
#include "Skeleton.h"
#include "FrameRate.h"
#include "Math.h"
#include "map.h"
#include "Item.h"
#include "HighScore.h"

using namespace std;
using namespace sf;

void SpawnItems(vector<Item>& items, int count)
{
	items.clear();
	for (int i = 0; i < count; i++)
	{
		Item newItem;
		float randomX = (rand() % (1600 - 250 + 1) + 250);
		float randomY = (rand() % (800 - 200 + 1) + 200);

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


	tMap map;
	Skeleton skeleton;
	Player player;
	FrameRate framerate;
	

	player.Initialize();
	framerate.Initialize();


	map.Load();
	player.Load();
	framerate.Load();

	
	int health = 3;
	Texture heartTexture;
	if (!heartTexture.loadFromFile("Project1/assets/texture/heart2.png"))
	{
		cout << "Chyba: Nelze nacist heart.png" << endl;
	}
	vector<Sprite> hpHearts;
	for (int i = 0; i < 3; i++)
	{
		Sprite heartSprite(heartTexture);
		heartSprite.setTexture(heartTexture);

		heartSprite.setScale({ 0.1f, 0.1f });

		heartSprite.setPosition({ 20.0f + (i * 40.0f), 90.0f });

		hpHearts.push_back(heartSprite);
	}

	vector<RectangleShape> powerUps;
	float powerUpSpawnTimer = 0.0f;
	float powerUpSpawnRate = 15000.0f;
	bool isTimeSlowed = false;
	float slowTimeTimer = 0.0f;
	float slowDuration = 3000.0f;

	int currentLevel = 1;
	int score = 0;

	vector<RectangleShape> magnets;
	float magnetSpawnTimer = 0.0f;
	float magnetSpawnRate = 30000.0f;
	float magnetDurationTimer = 0.0f;
	float magnetDuration = 6000.0f;
	bool isMagnetInUse = false;

	vector<Item> activeItems;
	int itemsCollected = 0;
	int itemsNeeded = 5;
	
	vector<Bullet> enemyBullets;
	float enemySpawnTimer = 0;
	float currentSpawnRate = 800.0f;
	float enemyBulletSpeed = 0.5f;
	
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

	Music music;
	if (!music.openFromFile("Project1/assets/audio/gameplaymusic.wav"))
	{
		cout << "ERROR: Could not load music file!" << endl;
	}

	music.setLooping(true); 
	music.setVolume(50.f);  

	Music gameOverBgm;
	if (!gameOverBgm.openFromFile("Project1/assets/audio/menumusic.wav"))
	{
		cout << "ERROR: Could not load game over music!" << endl;
	}
	gameOverBgm.setLooping(true);
	gameOverBgm.setVolume(50.f);
	gameOverBgm.setPitch(0.7f);

	float musicDelayTimer = 0.0f;
	bool isMusicWaiting = true;
	float delayAmount = 1000;

	HighScore highScoreTracker;
	string scoreFilePath = "Project1/assets/highscore.txt";
	highScoreTracker.loadFromFile(scoreFilePath);

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
			map.Update(deltaTime);
			framerate.Update(deltaTime,skeleton);
			skeleton.Update();
			player.Update(deltaTime, skeleton, mousePosition);

			enemySpawnTimer += deltaTime;
			if (isMusicWaiting)
			{
				musicDelayTimer += deltaTime;
				if (musicDelayTimer >= delayAmount)
				{
					music.play();
					isMusicWaiting = false;
				}
			}
			if (enemySpawnTimer >= currentSpawnRate)
			{
				SpawnBullets(enemyBullets, player.sprite.getPosition(), enemyBulletSpeed);
				enemySpawnTimer = 0;
			}



			for (auto& item : activeItems)
			{
				item.Update(deltaTime);
			}

			for (int i = 0; i < activeItems.size(); i++)
			{
				if (Math::checkRectCollision(player.GetHitBoxBoundsBoundingRectangle2(), activeItems[i].GetGlobalBounds()))
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
				if (currentLevel <= 5)
				{
					currentSpawnRate -= 15;
					enemyBulletSpeed += 0.030f;
				}
				else if (currentLevel > 5 && currentLevel <= 15)
				{
					currentSpawnRate -= 30;
					enemyBulletSpeed += 0.075f;
				}
				
				itemsCollected = 0;
				music.setPitch(1.0f + (currentLevel * 0.02f));
				if (currentLevel <= 7)
				{
					itemsNeeded++;
				}
				enemyBullets.clear();

				SpawnItems(activeItems, itemsNeeded);

				player.sprite.setPosition({ 990,525 });
			}
			powerUpSpawnTimer += deltaTime;
			if (powerUpSpawnTimer >= powerUpSpawnRate)
			{
				powerUpSpawnTimer = 0.0f;
				RectangleShape bonus;
				bonus.setSize({ 25.0f,25.0f });
				bonus.setFillColor(Color(0, 255, 255));
				bonus.setOutlineColor(Color::White);
				bonus.setOutlineThickness(2.0f);
				bonus.setPosition({ (float)(rand() % 1800 + 100), (float)(rand() % 900 + 100) });

				powerUps.push_back(bonus);

			}

			if (currentLevel >= 3)
			{
				magnetSpawnTimer += deltaTime;
				if (magnetSpawnTimer >= magnetSpawnRate)
				{
					magnetSpawnTimer = 0.0f;
					RectangleShape magnet;
					magnet.setSize({ 25.0f,25.0f });
					magnet.setFillColor(Color::Red);
					magnet.setOutlineColor(Color::White);
					magnet.setOutlineThickness(2.0f);
					magnet.setPosition({ (float)(rand() % 1800 + 100), (float)(rand() % 900 + 100) });

					magnets.push_back(magnet);
				}
			}
			for (int i = 0; i < magnets.size(); i++)
			{
				if (Math::checkRectCollision(player.GetHitBoxBoundsBoundingRectangle2(), magnets[i].getGlobalBounds()))
				{
					magnets.erase(magnets.begin() + i);
					isMagnetInUse = true;
					magnetDurationTimer = 0.0f;
					break;

				}
			}

			if (isMagnetInUse)
			{
				magnetDurationTimer += deltaTime;

				
				player.boundingRectangle2.setSize({ 600.f, 600.f });

			
				player.boundingRectangle2.setPosition(player.sprite.getPosition() + Vector2f(-268.f, -268.f));

				if (magnetDurationTimer >= magnetDuration)
				{
					isMagnetInUse = false; 
				}
			}
			else
			{
				player.boundingRectangle2.setSize({ 50.f, 50.f });

				player.boundingRectangle2.setPosition(player.sprite.getPosition() + Vector2f(7.f, 7.f));
			}

			for (int i = 0; i < powerUps.size(); i++)
			{
				if (Math::checkRectCollision(player.GetHitBoxBoundsBoundingRectangle2(), powerUps[i].getGlobalBounds()))
				{
					powerUps.erase(powerUps.begin() + i); 
					isTimeSlowed = true;
					slowTimeTimer = 0.0f; 
					break;
				}
			}
			float bulletDeltaTime = deltaTime;

			if (isTimeSlowed)
			{
				slowTimeTimer += deltaTime;
				bulletDeltaTime = deltaTime * 0.3f;

				if (slowTimeTimer >= slowDuration)
				{
					isTimeSlowed = false;
				}
			}

			for (int i = 0; i < enemyBullets.size(); i++)
			{
				enemyBullets[i].Update(bulletDeltaTime);

				if (Math::checkRectCollision(player.GetHitboxBounds(), enemyBullets[i].GetGlobalBounds()))
				{
					health--;
					player.isHit = true;

					if (health <= 0)
					{
						isGameOver = true;
						highScoreTracker.writeToFile(score, scoreFilePath);
						break; 
					}
					else
					{
						enemyBullets.erase(enemyBullets.begin() + i);
						i--; 
						continue; 
					}
				}

				Vector2f pos = enemyBullets[i].GetGlobalBounds().position;
				if (pos.x < -500 || pos.x > 2500 || pos.y < -500 || pos.y > 1500)
				{
					enemyBullets.erase(enemyBullets.begin() + i);
					i--;
				}
			}



		}
		else {
			if (music.getStatus() == SoundSource::Status::Playing)
			{
				music.stop();
			}
			if (gameOverBgm.getStatus() != SoundSource::Status::Playing)
			{
				gameOverBgm.play();
			}
			if (Keyboard::isKeyPressed(Keyboard::Scan::Enter))
			{
				isGameOver = false;
				currentLevel = 1;
				score = 0;
				itemsCollected = 0;
				itemsNeeded = 5;
				gameOverBgm.stop();
				music.setPitch(1.0f);
				player.isHit = false;

				isMusicWaiting = true;
				musicDelayTimer = 0.0f;

				currentSpawnRate = 800.0f;
				enemyBulletSpeed = 0.5f;
				enemySpawnTimer = 0;

				powerUps.clear();
				powerUpSpawnTimer = 0.0f;
				isTimeSlowed = false;
				slowTimeTimer = 0.0f;
				health = 3;

				magnets.clear();
				magnetSpawnTimer = 0.0f;
				isMagnetInUse = false;
				magnetDurationTimer = 0.0f;
				player.boundingRectangle2.setSize({ 50.f, 50.f });

				enemyBullets.clear();
				SpawnItems(activeItems, itemsNeeded);
				player.sprite.setPosition({ 990.0f, 525.0f });

			}
		}
		uiText.setString("Level: " + to_string(currentLevel) +
			"   |   Items: " + to_string(itemsCollected) + " / " + to_string(itemsNeeded) + "   |   Score: " + to_string(score) + "   |   High Score: " + to_string(highScoreTracker.currentHighScore));

		window.clear(Color::Black);

		map.Draw(window);

		for (auto& item : activeItems)
		{
			item.Draw(window);
		}

		for (auto& bonus : powerUps)
		{
			window.draw(bonus);
		}

		for (int i = 0; i < health; i++)
		{
			window.draw(hpHearts[i]);
		}

		for (auto& mag : magnets)
		{
			window.draw(mag);
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