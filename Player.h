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
	float movementSpeed = 0.7f;
	float bulletSpeed;
	float maxFireRate;
	float fireRateTimer;
	int XIndex = 0;
	int YIndex = 0;
	bool isFacingLeft = false;
	Vector2i size;

	RectangleShape boundingRectangle;
	RectangleShape boundingRectangle2;

public:
	Sprite sprite;
 


public:
	Player() : sprite(texture), maxFireRate(100), fireRateTimer(0) {}

	void Initialize();
	void Load();
	void Update(float deltaTime, Skeleton& skeleton, Vector2f &mousePosition);
	void Draw(RenderWindow &window);
	inline const FloatRect GetHitboxBounds() const
	{
		return boundingRectangle.getGlobalBounds();
	}
	inline const FloatRect GetHitBoxBoundsBoundingRectangle2() const
	{
		return boundingRectangle2.getGlobalBounds();
	}
};

