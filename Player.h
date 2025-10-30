#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include "Skeleton.h"

using namespace std;
using namespace sf; 
class Player
{
private:
	Texture texture;
	vector<RectangleShape>bullets;
	float movementSpeed = 1;
	float bulletSpeed = 0.5;
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
	void Update(float deltaTime, Skeleton& skeleton);
	void Draw(RenderWindow &window);
};

