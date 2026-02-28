#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Skeleton.h"
#include "Bullet.h"

using namespace std;
using namespace sf; 
class Player
{
private:
	Texture texture;
	vector<Bullet>bullets;
	float movementSpeed = 0.5;
	float bulletSpeed;
	float maxFireRate;
	float fireRateTimer;
	Vector2i size;

	RectangleShape boundingRectangle;

public:
	Sprite sprite;
 


public:
	Player() : sprite(texture), maxFireRate(100), fireRateTimer(0) {}

	void Initialize();
	void Load();
	void Update(float deltaTime, Skeleton& skeleton, Vector2f &mousePosition);
	void Draw(RenderWindow &window);
};

