#pragma once
#include <SFML/Graphics.hpp>

using namespace sf;

class Item
{
private:
	RectangleShape shape;

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

