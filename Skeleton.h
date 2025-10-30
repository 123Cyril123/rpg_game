#pragma once
#include <SFML/Graphics.hpp>
using namespace sf;

class Skeleton
{
private:
	Texture texture;
	Vector2i size;
	
	Font font;
	Text healthText;
	RectangleShape boundingRectangle;

public:
	Sprite sprite;
	int health;

public:
	Skeleton();
	~Skeleton();

	void changeHealth(int hp);
	void Initialize();
	void Load();
	void Update();
	void Draw(RenderWindow &window);
};

