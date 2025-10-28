#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Skeleton
{
private:
	Texture texture;
	Vector2i size;

	RectangleShape boundingRectangle;

public:
	Sprite sprite;

public:
	Skeleton() : sprite(texture) {}

	void Initialize();
	void Load();
	void Update();
	void Draw(RenderWindow &window);
};

