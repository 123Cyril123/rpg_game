#pragma once

#include <SFML/Graphics.hpp>
using namespace sf;

class Bullet
{
private:
	RectangleShape rectangleshape;
	
public:
	float speed;
	Vector2f direction;
	
	Bullet();
	~Bullet();

	void Initialize(const Vector2f &position,const Vector2f &target, float speed);
	void Load();
	void Update(float deltatime);
	void Draw(RenderWindow& window);

	inline const FloatRect GetGlobalBounds() const
	{
		return rectangleshape.getGlobalBounds();
	}
};

