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
	float bulletSpeed = 4;
	Vector2i size;

	RectangleShape boundingRectangle;

public:
	Sprite sprite;
 


public:
	Player() : sprite(texture) {}

	void Initialize();
	void Load();
	void Update(Skeleton& skeleton);
	void Draw(RenderWindow &window);
};

