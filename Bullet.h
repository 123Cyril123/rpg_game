#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
using namespace sf;
using namespace std;

class Bullet
{
private:
	RectangleShape rectangleshape;
	static Texture texture;
	static bool textureLoaded;
	
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

