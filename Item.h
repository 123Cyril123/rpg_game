#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace sf;
using namespace std;

class Item
{
private:
	RectangleShape shape;
	static Texture texture;
	static bool textureLoaded;

public:
	Item();
	~Item();

	void Initialize(Vector2f position);
	void Update(float deltaTime);
	void Draw(RenderWindow& window);

	inline const FloatRect GetGlobalBounds() const
	{
		return shape.getGlobalBounds();
	}
};

